/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Graphics.h"
#include "Sprite.h"
#include "../ui/FontInfo.h"
#include "../ui/Font.h"
#include "../ui/Text.h"
#include "../2d/Camera.h"

NAMESPACE_ALA
{
// ==========================================
// Basic
// ==========================================
ALA_CLASS_SOURCE_2(ala::Graphics, ala::Initializable, ala::Releasable)

Graphics* Graphics::__instance( NULL );

Graphics::Graphics():
  _logger( "ala::Graphics" ),
  _directX( 0 ),
  _directXDevice( 0 ),
  _directXSprite( 0 ) {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
  _logger.info( "Created" );
}

Graphics::~Graphics() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
  _logger.info( "Released" );
}

Graphics* Graphics::get() {
  if ( __instance == NULL ) {
    __instance = new Graphics();
  }
  return __instance;
}

void Graphics::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  initDirectX();

  setToInitialized();
}

void Graphics::release() {
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));

  setToReleasing();

  releaseDirectX();

  setToReleased();

  // destroy
  delete this;
}

void Graphics::onBackgroundToForeground() {}

// ==========================================
// Platform specific
// ==========================================

void Graphics::initDirectX() {
  HRESULT result;

  // init DirectX
  _directX = Direct3DCreate9( D3D_SDK_VERSION );
  ALA_ASSERT(!FAILED(_directX));
  _logger.info( "Initialized DirectX" );

  // init DirectX device
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp, sizeof(d3dpp));
  d3dpp.BackBufferCount = 1;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  d3dpp.BackBufferWidth = _directXBackBufferWidth;
  d3dpp.BackBufferHeight = _directXBackBufferHeight;
  d3dpp.Windowed = TRUE;
  d3dpp.hDeviceWindow = _hWnd;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  result = _directX->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    _hWnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &d3dpp,
    &_directXDevice );

  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXDevice));
  _logger.info( "Created DirectX Device" );


  // init DirectX Sprite
  result = D3DXCreateSprite( _directXDevice, &_directXSprite );
  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXSprite));
  _logger.info( "Created DirectX Sprite" );

  // init DirectX Line
  result = D3DXCreateLine(_directXDevice, &_directXLine);
  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXLine));
  _directXLine->SetGLLines(FALSE);
  _directXLine->SetAntialias(TRUE);
  _logger.info("Created DirectX Line");
}

void Graphics::releaseDirectX() {
  if(_directXLine) {
    _directXLine->Release();
    _logger.info("Released DirectX Line");
  }
  if ( _directXSprite ) {
    _directXSprite->Release();
    _logger.info( "Released DirectX Sprite" );
  }
  if ( _directXDevice ) {
    _directXDevice->Release();
    _logger.info( "Released DirectX Device" );
  }
  if ( _directX ) {
    _directX->Release();
    _logger.info( "Released DirectX" );
  }
}

bool Graphics::beginRendering() {
  // clear screen
  if ( _directXDevice->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 ) != D3D_OK ) {
    _directXDevice->Present( 0, 0, 0, 0 );
    return false;
  }

  // start rendering
  if ( _directXDevice->BeginScene() != D3D_OK ) {

    _directXDevice->Present( 0, 0, 0, 0 );
    return false;
  }

  _directXDevice->SetTransform(D3DTS_PROJECTION, &_projectionMatrix);
  _directXDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);
  _directXDevice->SetTransform(D3DTS_VIEW, &_viewMatrix);

  if ( _directXSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK ) != D3D_OK ) {
    _directXDevice->EndScene();
    _directXDevice->Present( 0, 0, 0, 0 );
    return false;
  }

  _directXLine->SetGLLines(FALSE);
  _directXLine->SetAntialias(TRUE);
  _directXLine->SetWidth(_directXLineWidth);

  if(_directXLine->Begin() != D3D_OK) {
    _directXSprite->End();
    _directXDevice->EndScene();
    _directXDevice->Present(0, 0, 0, 0);
    return false;
  }

  return true;
}

void Graphics::endRendering() {
  // stop rendering
  _directXLine->End();
  _directXSprite->End();
  _directXDevice->EndScene();

  // display back buffer to screen
  _directXDevice->Present( 0, 0, 0, 0 );
}

void Graphics::loadSprite( Sprite* sprite ) {
  if( sprite->getSourceFile().empty()) {
    loadEmptySprite(sprite);
    return;
  }

  if ( sprite->getDirectXTexture() ) {
    sprite->getDirectXTexture()->Release();
  }
  HRESULT result;

  // load image info
  D3DXIMAGE_INFO info;
  result = D3DXGetImageInfoFromFile( sprite->getSourceFile().c_str(), &info );
  ALA_ASSERT(result == D3D_OK);

  // create texture
  LPDIRECT3DTEXTURE9 texture = NULL;
  D3DXCreateTextureFromFileEx(
    _directXDevice, //Direct3D device object
    sprite->getSourceFile().c_str(), //bitmap filename
    info.Width, //bitmap image width
    info.Height, //bitmap image height
    1, //mip-map levels (1 for no chain)
    D3DPOOL_DEFAULT, //the type of surface (standard)
    D3DFMT_UNKNOWN, //surface format (default)
    D3DPOOL_DEFAULT, //memory class for the texture
    D3DX_DEFAULT, //image filter
    D3DX_DEFAULT, //mip filter
    D3DCOLOR_XRGB(sprite->getTransColor().getR(), sprite->getTransColor().getG(), sprite->getTransColor().getB()), //color key for transparency
    &info, //bitmap file info (from loaded file)
    NULL, //color palette
    &texture ); //destination texture

  ALA_ASSERT(result == D3D_OK);
  sprite->setDirectXTexture( texture );
  sprite->setContentSize( Size( static_cast<float>(info.Width), static_cast<float>(info.Height) ) );
}

void Graphics::loadEmptySprite( Sprite* sprite ) {
  if (sprite->getDirectXTexture()) {
    sprite->getDirectXTexture()->Release();
  }
  HRESULT result;

  // create texture
  LPDIRECT3DTEXTURE9 texture = NULL;
  result = D3DXCreateTexture(
    _directXDevice, //Direct3D device object
    1, //bitmap image width
    1, //bitmap image height
    1, //mip-map levels (1 for no chain)
    D3DPOOL_DEFAULT, //the type of surface (standard)
    D3DFMT_UNKNOWN, //surface format (default)
    D3DPOOL_DEFAULT, //memory class for the texture
    &texture); //destination texture
  D3DXFillTexture(texture, Graphics::fillDirectXTextureRed, LPVOID( &sprite->getTransColor() ));

  ALA_ASSERT(result == D3D_OK);
  sprite->setDirectXTexture(texture);
  sprite->setContentSize(Size(static_cast<float>(1), static_cast<float>(1)));
}

void Graphics::setLineWidth( float width ) {
  _directXLineWidth = width;
}

ID3DXFont* Graphics::loadDirectXFont ( std::string fontName, const FontInfo& fontInfo ) const
{
  ID3DXFont* font;

  D3DXCreateFont(
    _directXDevice,		// device
    fontInfo.getFontHeight(),									// font height
    0,												// font width
    convertToDirectXFontWeight ( fontInfo.getFontWeight (  ) ),									// font weight
    1,												//
    fontInfo.getItalic (  ),										// italic
    DEFAULT_CHARSET,
    OUT_DEFAULT_PRECIS,
    ANTIALIASED_QUALITY,
    FF_DONTCARE,
    fontName.c_str (  ),										// font face
    &font										// pointer font
  );

  return font;
}

void Graphics::drawSprite( Sprite* sprite, const Vec2& origin, const Mat4& transformMatrix, const Color& backColor, const Rect& srcRect, const int zIndex ) {
  LPDIRECT3DTEXTURE9 texture = sprite->getDirectXTexture();
  ALA_ASSERT(texture);

  RECT dSrcRect = convertToWindowsRect( srcRect );

  D3DXVECTOR3 dPostition;
  dPostition.x = 0;
  dPostition.y = 0;
  dPostition.z = 0;

  D3DXMATRIX oldMatrix;

  // reverse z index for back-to-front rendering
  float reverseZIndex = MAX( ALA_CAMERA_MAX_Z - zIndex, ALA_CAMERA_MIN_Z );
  auto translationMatrix = Mat4::getTranslationMatrix(0, 0, reverseZIndex);
  auto flipMatrix = Mat4::getScalingMatrix(1, -1, 1);

  auto transformationMatrix = convertToDirectXMatrix(translationMatrix*flipMatrix* transformMatrix);

  _directXSprite->GetTransform( &oldMatrix );

  D3DXMATRIX finalMatrix = transformationMatrix * oldMatrix;

  _directXSprite->SetTransform( &finalMatrix );

  D3DXVECTOR3 center = D3DXVECTOR3( abs( dSrcRect.right - dSrcRect.left ) * origin.getX(), abs( dSrcRect.top - dSrcRect.bottom ) * (1 - origin.getY()), 0 );

  if ( srcRect.getSize().getWidth() == 0 || srcRect.getSize().getHeight() == 0 ) {
    _directXSprite->Draw(
      texture,
      NULL,
      &center,
      &dPostition,
      D3DXCOLOR( backColor.getR() / 256.f, backColor.getG() / 256.f, backColor.getB() / 256.f, backColor.getA() / 256.f ) );
  }
  else {
    _directXSprite->Draw(
      texture,
      &dSrcRect,
      &center,
      &dPostition,
      D3DXCOLOR( backColor.getR() / 256.f, backColor.getG() / 256.f, backColor.getB() / 256.f, backColor.getA() / 256.f ) );
  }

  _directXSprite->SetTransform( &oldMatrix );
}

void Graphics::drawText ( Font* font, const FontInfo& fontInfo, const std::string& text, const Rect& boundingRect,
  const int horizontalAlignment, const int verticalAlignment, const Color& textColor, const Mat4& transformMatrix, const int zIndex )
{
  D3DXMATRIX oldMatrix;

  const auto flipMatrix = Mat4::getScalingMatrix(1, -1, 1);

  const auto transformationMatrix = convertToDirectXMatrix(flipMatrix*transformMatrix);

  _directXSprite->GetTransform(&oldMatrix);

  D3DXMATRIX finalMatrix = transformationMatrix * oldMatrix;

  _directXSprite->SetTransform(&finalMatrix);

  auto directXFont = font->getDirectXFont(fontInfo);

  RECT directXRect;
  directXRect.left = static_cast<LONG>(boundingRect.getTopLeft().getX());
  directXRect.top = -static_cast<LONG>(boundingRect.getTopLeft().getY());
  directXRect.right = static_cast<LONG>(boundingRect.getTopLeft().getX() + boundingRect.getSize().getWidth());
  directXRect.bottom = static_cast<LONG>(-boundingRect.getTopLeft().getY() + boundingRect.getSize().getHeight());

  const auto directXTextFormat = convertToDirectXTextFormat(horizontalAlignment, verticalAlignment);
  const auto directXTextColor = D3DXCOLOR(textColor.getR() / 256.f, textColor.getG() / 256.f, textColor.getB() / 256.f, textColor.getA() / 256.f);

  directXFont->DrawTextA(_directXSprite, text.c_str(), -1, &directXRect, directXTextFormat, directXTextColor);

  _directXSprite->SetTransform(&oldMatrix);
}

void Graphics::drawLine(const std::vector<Vec2>& vertices, const Color& color) {
  D3DXVECTOR2* arr = new D3DXVECTOR2[vertices.size()];

  for (size_t i = 0; i < vertices.size(); i++) {
    const auto& vec = vertices[i];
    arr[i] = D3DXVECTOR2(vec.getX(), vec.getY());
  }
  _directXLine->Draw(arr, vertices.size(),
    D3DCOLOR_ARGB(color.getA(), color.getR(), color.getG(), color.getB()));
  delete[]arr;
}

void Graphics::drawLine(const std::vector<Vec2>& vertices, const Mat4& transformMatrix, const Color& color, const int zIndex) {
  D3DXVECTOR3* arr = new D3DXVECTOR3[vertices.size()];

  for (size_t i = 0; i < vertices.size(); i++) {
    const auto& vec = vertices[i];
    arr[i] = D3DXVECTOR3(vec.getX(), vec.getY(), 0);
  }

  D3DXMATRIX oldMatrix;

	// reverse z index for back-to-front rendering
	float reverseZIndex = MAX(ALA_CAMERA_MAX_Z - zIndex, ALA_CAMERA_MIN_Z);

	D3DXMATRIX matProj, matView;
	D3DXVECTOR3 vEye(0.0f, 0.0f, -50), vAt(0.0f, 0.0f, 0.0f), vUp(0.0f, 1.0f, 0.0f);
	D3DXMatrixOrthoOffCenterLH(&matProj, 0.0f, GameManager::get()->getVisibleWidth(), GameManager::get()->getVisibleHeight(), 0.0f, ALA_CAMERA_MIN_Z, ALA_CAMERA_MAX_Z);
	D3DXMatrixLookAtLH(&matView, &vEye, &vAt, &vUp);

  auto translationMatrix = Mat4::getTranslationMatrix(0, 0, reverseZIndex);
  auto flipMatrix = Mat4::getScalingMatrix(1, -1, 1);
  auto transformationMatrix = convertToDirectXMatrix(/*translationMatrix*flipMatrix**/ transformMatrix)*matView*matProj;
  _directXSprite->GetTransform(&oldMatrix);
  D3DXMATRIX finalMatrix = transformationMatrix * oldMatrix;

  _directXLine->DrawTransform(arr, vertices.size(), 
    &finalMatrix,
    D3DCOLOR_ARGB(color.getA(), color.getR(), color.getG(), color.getB()));
  delete[]arr;
}

D3DXMATRIX Graphics::convertToDirectXMatrix( const Mat4& mat ) const {

  D3DXMATRIX result;
  result._11 = mat.get11();
  result._12 = mat.get12();
  result._13 = mat.get13();
  result._14 = mat.get14();

  result._21 = mat.get21();
  result._22 = mat.get22();
  result._23 = mat.get23();
  result._24 = mat.get24();

  result._31 = mat.get31();
  result._32 = mat.get32();
  result._33 = mat.get33();
  result._34 = mat.get34();

  result._41 = mat.get41();
  result._42 = mat.get42();
  result._43 = mat.get43();
  result._44 = mat.get44();

  return result;
}

RECT Graphics::convertToWindowsRect( const Rect& srcRect ) const {
  RECT desRect;
  desRect.left = static_cast<LONG>(srcRect.getTopLeft().getX());
  desRect.top = static_cast<LONG>(srcRect.getTopLeft().getY());
  desRect.right = static_cast<LONG>(srcRect.getTopLeft().getX() + srcRect.getSize().getWidth());
  desRect.bottom = static_cast<LONG>(srcRect.getTopLeft().getY() + srcRect.getSize().getHeight());
  return desRect;
}

DWORD Graphics::convertToDirectXFontWeight ( const int fontWeight ) const
{
  switch ( fontWeight )
  {
  case ALA_FONT_WEIGHT_LIGHT:
    return FW_LIGHT;
  case ALA_FONT_WEIGHT_BOLD:
    return FW_BOLD;
  case ALA_FONT_WEIGHT_EXTRABOLD:
    return FW_EXTRABOLD;
  case ALA_FONT_WEIGHT_EXTRALIGHT:
    return FW_EXTRALIGHT;
  case ALA_FONT_WEIGHT_HEAVY:
    return FW_HEAVY;
  case ALA_FONT_WEIGHT_MEDIUM:
    return FW_MEDIUM;
  case ALA_FONT_WEIGHT_NORMAL:
    return FW_NORMAL;
  case ALA_FONT_WEIGHT_SEMIBOLD:
    return FW_SEMIBOLD;
  case ALA_FONT_WEIGHT_THIN:
    return FW_THIN;
  default:
    return FW_NORMAL;
  }
}

DWORD Graphics::convertToDirectXTextFormat ( const int horizontalAlignment, const int verticalAlignment )
{
  DWORD textFormat;
  switch ( horizontalAlignment )
  {
  case ALA_HORIZONTAL_ALIGNMENT_CENTER:
    textFormat = DT_CENTER;
    break;
  case ALA_HORIZONTAL_ALIGNMENT_LEFT:
    textFormat = DT_LEFT;
    break;
  case ALA_HORIZONTAL_ALIGNMENT_RIGHT:
    textFormat = DT_RIGHT;
    break;
  default:
    textFormat = DT_CENTER;
    break;
  }

  switch (verticalAlignment)
  {
  case ALA_VERTICAL_ALIGNMENT_MIDDLE:
    textFormat |= DT_VCENTER;
    break;
  case ALA_VERTICAL_ALIGNMENT_TOP:
    textFormat |= DT_TOP;
    break;
  case ALA_VERTICAL_ALIGNMENT_BOTTOM:
    textFormat |= DT_BOTTOM;
    break;
  default:
    textFormat |= DT_VCENTER;
    break;
  }

  return textFormat;
}

void Graphics::setProjectionMatrix ( const Mat4& mat )
{
  _projectionMatrix = convertToDirectXMatrix(mat);
}

void Graphics::setWorldMatrix ( const Mat4& mat )
{
  _worldMatrix = convertToDirectXMatrix(mat);
}

void Graphics::setViewMatrix ( const Mat4& mat )
{
  _viewMatrix = convertToDirectXMatrix(mat);
}

void Graphics::fillDirectXTextureRed(D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord, const D3DXVECTOR2* pTexelSize,
  LPVOID pData) {
  const auto color = static_cast<Color*>(pData);
  *pOut = D3DXVECTOR4(color->getR() / 255.f, color->getG() / 255.f, color->getB() / 255.f, color->getA() / 255.f);
}
}
