#ifndef __ALADDIN_CORE_APPLICATION_H__
#define __ALADDIN_CORE_APPLICATION_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Scene.h"
#include "ResourceInitializer.h"
#include "Logger.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Application, ala::Initializable, ala::Releasable)
  // ================================================
  // Basic
  // ================================================
private:
  // Configuration information
  std::string _title;
  int _resolutionWidth;
  int _resolutionHeight;
  int _screenWidth;
  int _screenHeight;
  bool _fullScreen;
  LARGE_INTEGER _animationInterval;
  std::vector<ResourceInitializer*> _resourceInitializers;

  // Debug information
  long _frameCount;
  Logger _logger;

public:
  Application();

  virtual ~Application();

  void setScreenSize( const int width, const int height );

  void setResolutionSize( const int width, const int height );

  int getResolutionWidth() const;

  int getResolutionHeight() const;

  bool isFullScreen() const;

  void setTitle( const std::string& title );

  const std::string& getTitle() const;

  void setAnimationInterval( const float interval );

  void setFps( const int fps );

  void setFullScreen();

  float getAnimationInterval() const;

  int getFps() const;

  void registerResourceInitializer( ResourceInitializer* initializer );

  // ================================================
  // Main Game Process
  // ================================================
  void startWithScene( Scene* scene );

private:
  void updateInput();

  void resolveLockedTasks();

  void updatePhysics( const float delta );

  void updateGame( const float delta );

  void renderGraphics();

  void backgroundToForeground();

  // ================================================
  // Initializing & Releasing
  // ================================================
public:
  void initialize() override;

  void release() override;

private:
  void initResources();

  void initComponents();

  void releaseComponents();

protected:
  /**
   * \brief Configuration goes here (screen size, title, fps, ...)
   */
  virtual void onPreInitialize() = 0;

  /**
   * \brief Set Scene to start here
   */
  virtual void onPostInitialize() = 0;

  virtual void onBackgroundToForeground();

  // ================================================
  // Platform specific
  // ================================================

private:
  int _logStream;
  bool _exiting;
  MSG _msg;
  HINSTANCE _hInstance;
  HWND _hWnd;

  LARGE_INTEGER _freq;

  _LARGE_INTEGER _startTimestamp;
  _LARGE_INTEGER _lastTimestamp;
  _LARGE_INTEGER _currentTimestamp;

  float _delta;
public:
  void run( const HINSTANCE hInstance,
            const HINSTANCE hPrevInstance,
            const LPSTR lpCmdLine,
            const int nCmdShow,
            const int logStream = 0 );

private:
  void initWindowHandle();

  void gameLoop();

  void processMessage();

  void processGame();

  static LRESULT wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
};
}

#endif //!__ALADDIN_CORE_APPLICATION_H__
