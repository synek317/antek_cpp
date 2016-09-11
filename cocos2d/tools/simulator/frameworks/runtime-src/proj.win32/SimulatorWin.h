#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "cocos2d.h"
#include "app_delegate.h"
#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"

class SimulatorWin
{
public:
    static SimulatorWin *getInstance();
    virtual ~SimulatorWin();
    int run();

    virtual void quit();
    virtual void relaunch();
    virtual void openNewPlayer();
    virtual void openNewPlayerWithProjectConfig(const ProjectConfig &config);
    virtual void openProjectWithProjectConfig(const ProjectConfig &config);

    virtual int getPositionX();
    virtual int getPositionY();
protected:
    SimulatorWin();

    static SimulatorWin *_instance;
    ProjectConfig _project;
    HWND _hwnd;
    HWND _hwndConsole;
    AppDelegate *_app;
    FILE *_writeDebugLogFile;

    //
    void setupUI();
    void setZoom(float frameScale);
    void updateWindowTitle();

    // debug log
    void writeDebugLog(const char *log);
    void parseCocosProjectConfig(ProjectConfig &config);

    //
    void onOpenFile(const std::string &filePath);
    void onOpenProjectFolder(const std::string &folderPath);
    void onDrop(const std::string &path);

    // helper
    std::string convertPathFormatToUnixStyle(const std::string& path);
    std::string getUserDocumentPath();
    std::string getApplicationExePath();
    std::string getApplicationPath();
    static char* convertTCharToUtf8(const TCHAR* src);

    static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

