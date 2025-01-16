// GDIPlusTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <Gdiplus.h>

using namespace std;


//int CALLBACK EnumFontFamExProc(//用于判断设备上下文是否拥有该字体的回调函数
//	ENUMLOGFONTEX* lpelfe,    // logical-font data
//	NEWTEXTMETRICEX* lpntme,  // physical-font data
//	DWORD FontType,           // type of font
//	LPARAM lParam             // application-defined data
//)
//{
//	//CString strName = lpelfe->elfLogFont.lfFaceName;
//	//MessageBox(NULL , strName , 0 , 0);
//	return 10;
//}
//
//BOOL isSystemHasFont(HDC hdc, CString fontName)//判断是否可以使用该字体
//{
//	CFont font;
//	if (font.CreatePointFont(12, fontName))
//	{
//		LOGFONTW lf;
//		wcscpy_s(lf.lfFaceName, min(LF_FACESIZE, fontName.GetLength() + 1), fontName.GetBuffer());
//		int iRet = EnumFontFamiliesExW(hdc, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)0, 0);
//		font.DeleteObject();
//		return iRet == 10 ? TRUE : FALSE;
//	}
//	return FALSE;
//}


static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = nullptr;
	{
		Gdiplus::GetImageEncodersSize(&num, &size);
		if (size == 0)
			return -1;  // Failure

		//pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));

		pImageCodecInfo = new Gdiplus::ImageCodecInfo[size];
		if (!pImageCodecInfo)
			return -1;  // Failure

		Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
	}

	for (UINT i = 0; i < num; ++i)
	{
		if (0 == wcscmp(pImageCodecInfo[i].MimeType, format))
			//if (0 == wcscmp(pImageCodecInfo[0].MimeType, format))
		{
			*pClsid = pImageCodecInfo[i].Clsid;
			//free(pImageCodecInfo);
			delete[] pImageCodecInfo;
			return i;  // Success
		}
	}

	//free(pImageCodecInfo);
	delete[] pImageCodecInfo;
	return -1;  // Failure
}



static bool createNameAvata(const std::wstring& name, const std::wstring& path)
{
	if (name.empty() || path.empty())
		return false;

	constexpr int v = 100;
	Gdiplus::Bitmap bitmap(v, v);
	Gdiplus::Graphics graphics(&bitmap);
	Gdiplus::SolidBrush brush(0xFF347AFC/*Gdiplus::Color::Blue*/);
	graphics.FillRectangle(&brush, 0, 0, v, v);

	Gdiplus::FontFamily fontFamily( L"Arial" /*L"Arial"*/ /*L"Microsoft YaHei"*/);
	Gdiplus::Status lastResult = fontFamily.GetLastStatus();
	if (Gdiplus::FontFamilyNotFound == lastResult) {
		int i = 0;
		i++;
		//FontFamilyNotFound
		return false;
	}


	float emSize = [&]()->float {
		float f = 28.0f;
		while (f > 15)
		{
			Gdiplus::Font myFont(&fontFamily, f, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
			Gdiplus::RectF boundingBox{ 0.00,0.00,0.00,0.00 };
			graphics.MeasureString(name.c_str(), -1, &myFont, { 0.00, 0.00 }, &boundingBox);
			if (v > boundingBox.Width)
				break;
			f--;
		}
		return f;
	}();



	Gdiplus::Font myFont(&fontFamily, emSize, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::RectF rect(0,0, v, v);
    //https://blog.csdn.net/lizhichao410/article/details/124793835
	//https://learn.microsoft.com/zh-cn/windows/win32/api/gdiplusenums/ne-gdiplusenums-stringformatflags
	//解决GDI+的DrawString绘制带有偏移的问题  https://www.cnblogs.com/cherishui/p/12747334.html 
	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentCenter);
	format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	//graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);   //字体平滑


	//检测字符串需要的矩形区域
	const Gdiplus::PointF origin{ 0.00,0.00 };
	Gdiplus::RectF boundingBox{0.00,0.00,0.00,0.00 };
	graphics.MeasureString(name.c_str(), (int)name.length(), &myFont, { 0.00, 0.00 }, &boundingBox);
	
	graphics.DrawString(name.c_str(), name.length(), &myFont, rect, &format, &blackBrush);
	CLSID pngClsid{ 0 };
	GetEncoderClsid(L"image/png", &pngClsid);
	bitmap.Save(path.c_str(), &pngClsid, NULL);

	return true;
}

//VOID Example_GetFamilyName(HDC hdc)
//{//https://learn.microsoft.com/en-us/windows/win32/api/Gdiplusheaders/nf-gdiplusheaders-fontfamily-getfamilyname

//	Graphics graphics(hdc);
//
//	// Create a FontFamily object.
//	FontFamily nameFontFamily(L"arial");
//
//	// Get the cell ascent of the font family in design units.
//	WCHAR      familyName[LF_FACESIZE];
//	nameFontFamily.GetFamilyName(familyName);
//
//	// Copy the cell ascent into a string and draw the string.
//	SolidBrush solidbrush(Color(255, 0, 0, 0));
//	Font       font(&nameFontFamily, 16);
//	graphics.DrawString(familyName, -1, &font, PointF(0, 0), &solidbrush);
//}

#include <atlstr.h>
int main()
{

	// 获取窗口当前显示的监视器
   // 使用桌面的句柄.
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// 获取监视器逻辑宽度与高度
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(hMonitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

	// 获取监视器物理宽度与高度
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	int cyPhysical = dm.dmPelsHeight;
	// 缩放比例计算  实际上使用任何一个即可
	double horzScale = ((double)cxPhysical / (double)cxLogical);
	double vertScale = ((double)cyPhysical / (double)cyLogical);
	printf("%lf  %lf\n", horzScale, vertScale);
	//assert(horzScale == vertScale); // 宽或高这个缩放值应该是相等的




	ULONG_PTR diplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&diplusToken, &gdiplusStartupInput, NULL);




	//{
	//	// Create a FontFamily object.
	//	Gdiplus::FontFamily nameFontFamily(L"Arial");

	//	// Get the cell ascent of the font family in design units.
	//	WCHAR      familyName[LF_FACESIZE];
	//	nameFontFamily.GetFamilyName(familyName);
	//	int i = 0;
	//	i += 1;
	//}

	{
		wstring name = LR"(立红)";
		//string namea = u8R"(姓名))）)";
		//wstring name = LPWSTR(ATL::CA2W(namea.c_str(), CP_UTF8));

		if (name.length() > 2) {
			name = name.substr(name.length() - 2);
		}


		wstring path = LR"(d:\var.png)";

		createNameAvata(name, path);


	}
	Gdiplus::GdiplusShutdown(diplusToken);

	std::cout << "Hello World!\n";
}
