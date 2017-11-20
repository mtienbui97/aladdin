#ifndef __ALADDIN_2D_GRAPHICS_2D_H__
#define __ALADDIN_2D_GRAPHICS_2D_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Rect.h"

NAMESPACE_ALA
{
  class Font;
  class FontInfo;
  class Sprite;

ALA_CLASS_HEADER_2(Graphics, ala::Initializable, ala::Releasable)
  // ==========================================
  // Basic
  // ==========================================
  friend class Application;

private:
  static Graphics* __instance;
  Logger _logger;

public:
  Graphics();

  virtual ~Graphics();

  static Graphics* get();

  void initialize() override;

  void release() override;

  void onBackgroundToForeground();

  // ==========================================
  // Platform specific
  // ==========================================
private:
  HINSTANCE _hInstance;
  HWND _hWnd;
  UINT _directXBackBufferWidth;
  UINT _directXBackBufferHeight;
  IDirect3D9* _directX;
  IDirect3DDevice9* _directXDevice;
  LPD3DXSPRITE _directXSprite;
  FLOAT _directXLineWidth;
  LPD3DXLINE _directXLine;

  D3DXMATRIX _projectionMatrix;
  D3DXMATRIX _worldMatrix;
  D3DXMATRIX _viewMatrix;
public:
  void initDirectX();

  void releaseDirectX();

  bool beginRendering();

  void endRendering();

  void loadSprite( Sprite* sprite );

  void loadEmptySprite(Sprite* sprite);

  void setLineWidth(float width);

  void drawLine(const std::vector<Vec2>& vertices, const Color& color);

  void drawLine(const std::vector<Vec2>& vertices, const Mat4& transformMatrix, const Color& color, const int zIndex);

  void drawSprite( Sprite* sprite, const Vec2& origin, const Mat4& transformMatrix, const Color& backColor, const Rect& srcRect, const int zIndex = 0 );

  void drawText(ala::Font* font, const FontInfo& fontInfo, const std::string& text, const Rect& boundingRect, const int horizontalAlignment, const int verticalAlignment, const Color& textColor, const Mat4& transformMatrix, const int zIndex = 0);

  ID3DXFont* loadDirectXFont(std::string fontName, const FontInfo &fontInfo) const;

  D3DXMATRIX convertToDirectXMatrix( const Mat4& mat ) const;

  RECT convertToWindowsRect( const Rect& rect ) const;

  DWORD convertToDirectXFontWeight(const int fontWeight) const;

  DWORD convertToDirectXTextFormat(const int horizontalAlignment, const int verticalAlignment);

  void setProjectionMatrix( const Mat4& mat );

  void setWorldMatrix( const Mat4& mat );
  
  void setViewMatrix( const Mat4& mat );

  static VOID WINAPI fillDirectXTextureRed(D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord, const D3DXVECTOR2* pTexelSize, LPVOID pData);
};
}

#endif //!__ALADDIN_2D_GRAPHICS_2D_H__
