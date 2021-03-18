#pragma once

#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>

#include <wrl.h>

#include <vector>
#include <string>

#include "gap.h"

using namespace std;
using namespace D2D1;
using namespace Microsoft::WRL;

#define ADDITIONAL_TOP_OFFSET    0
#define ADDITIONAL_BOTTOM_OFFSET this->FontSize * ((int)this->Paragraphs.size() - 1)

#define FONT_RESIZING_SCALAR 5.0f
#define TEXT_SCROLLING_SCALAR this->FontSize

#define LOWEST_FONT_SIZE 10.0f
#define HIGHEST_FONT_SIZE 100.0f

#define NORMALIZE(delta,value) delta == 65416.0f ? -value : value

class Renderer
{
	public:
		Renderer(HWND window);
	   ~Renderer();

	   void OnScroll(float delta);
	   void OnCtrlScroll(float delta);
	   void OnResize(UINT width, UINT height);

	   void RenderText(Gap* gap);
	   void RenderCursor(size_t pos);

	   void SetParagraphs(vector<Paragraph> prs);

	private:
		HWND Window;
		RECT SurfaceRect;

		wchar_t* Text;
		float FontSize;
		float ScrollOffset;

		vector<Paragraph> Paragraphs;
		
		ID2D1Factory* Direct2DFactory;
		IDWriteFactory* DWriteFactory;
		ID2D1DeviceContext* Direct2DContext;
		ID2D1HwndRenderTarget* Direct2DTarget;
		
		ComPtr<IDWriteTextFormat> DWriteTextFormat;
		ComPtr<ID2D1SolidColorBrush> Direct2DTextBrush;
		ComPtr<ID2D1SolidColorBrush> Direct2DCursorBrush;

		void CreateDWriteFactory();
		void CreateDirect2DTarget();
		void CreateDirect2DFactory();
		void CreateDirect2DContext();

		ComPtr<ID2D1SolidColorBrush> CreateDirect2DBrush(
			ColorF color = ColorF::WhiteSmoke
		);
		ComPtr<IDWriteTextLayout> CreateDWriteTextLayout(
			wstring text,
			UINT textLen,
			float maxWidth = 0,
			float maxHeight = 0
		);
		ComPtr<IDWriteTextFormat> CreateDWriteTextFormat(
			float fontSize,
			wstring fontFamily = L"Consolas", 
			DWRITE_FONT_WEIGHT  fontWeight  = DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE   fontStyle   = DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL
		);

		void RenderTextWithDirect2DContext();

		void CreateResources();
		void DiscardResources();
};