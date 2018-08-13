#include "Direct2D.h"

#include <Framework/Window.h>

namespace
{
	ComPtr<ID2D1Factory> factory;
	ComPtr<ID2D1HwndRenderTarget> renderTarget;

	ComPtr<IDWriteFactory> writeFactory;
	ComPtr<IDWriteTextFormat> characterFormat;
	ComPtr<IDWriteTextFormat> textFormat;

	std::vector<ID2Object*> d2objects;
	std::vector<IResource*> resources;

	HRESULT createResources()
	{
		if (!renderTarget.get())
		{
			RECT rc;
			GetWindowRect(Window::getHandle(), &rc);

			HRESULT hr = factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(
					Window::getHandle(),
					D2D1::SizeU(
						rc.right,
						rc.bottom)),
				&renderTarget);
			if (FAILED(hr))
			{
				MB_FAILED(L"CreateHwndRenderTarget", hr);

				return hr;
			}

			for (IResource* resource : resources)
			{
				hr = resource->create();
				if (FAILED(hr))
				{
					return hr;
				}
			}
		}

		return ERROR_SUCCESS;
	}

	void releaseResources()
	{
		renderTarget.release();

		for (IResource* resource : resources)
		{
			resource->release();
		}
	}
}

namespace Direct2D
{
	bool initialize()
	{
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&factory);
		if (FAILED(hr))
		{
			return false;
		}

		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			(IUnknown**) &writeFactory);
		if (FAILED(hr))
		{
			return false;
		}

		hr = writeFactory->CreateTextFormat(
			L"Arial",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			40,
			L"de-de",
			&textFormat);

		return true;
	}

	void onCreate()
	{
		if (FAILED(createResources()))
		{
			MessageBox(
				NULL,
				L"Unable to create resources",
				L"Error",
				MB_OK);

			::exit(0);
		}
	}

	void onPaint()
	{
		HRESULT hr = createResources();
		if (SUCCEEDED(hr))
		{
			renderTarget->BeginDraw();
			renderTarget->Clear(D2D1::ColorF(
				D2D1::ColorF::Black));
				
			for (ID2Object* object : d2objects)
			{
				object->draw();
			}

			hr = renderTarget->EndDraw();
		}

		if (hr == D2DERR_RECREATE_TARGET)
		{
			releaseResources();
		}
	}

	void onSize(
		UINT width,
		UINT height)
	{
		if (renderTarget.get())
		{
			renderTarget->Resize(D2D1::SizeU(
				width,
				height));
		}
	}

	void registerD2Object(
		ID2Object* object)
	{
		d2objects.push_back(object);
	}

	void registerResource(
		IResource* resource)
	{
		resources.push_back(resource);
	}

	void recreateResources()
	{
		releaseResources();
		createResources();
	}

	void removeAllObjects()
	{
		d2objects.clear();
	}

	void removeAllResources()
	{
		for (IResource* resource : resources)
		{
			delete resource;
		}

		resources.clear();
	}

	D2D1_SIZE_F getWindowSize()
	{
		return renderTarget->GetSize();
	}

	ID2D1Factory* getFactory()
	{
		return factory.get();
	}

	ID2D1HwndRenderTarget* getHwndRenderTarget()
	{
		return renderTarget.get();
	}

	void createCharacterFormat(float tileSize)
	{
		characterFormat.release();
		HRESULT hr = writeFactory->CreateTextFormat(
			L"Arial",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			tileSize,
			L"de-de",
			&characterFormat);
		if (FAILED(hr))
		{
			MB_FAILED(L"CreateTextFormat", hr);
		}
	}

	IDWriteTextFormat* getCharacterFormat()
	{
		return characterFormat.get();
	}

	IDWriteTextFormat* getTextFormat()
	{
		return textFormat.get();
	}
}
