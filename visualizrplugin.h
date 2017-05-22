#ifndef VISUALIZRPLUGIN
#define VISUALIZRPLUGIN

#include <QtPlugin>

#include <QString>
#include <QOpenGLFunctions>
#include <QtCore/QtCore>

#define VisualizrPlugin_iid "Kramer.Visualizr.VisualizrPlugin/1.0"

// This class needs to be inhereted from visualizr plugins
class VisualizrPlugin {
public:
    // Override this to specify vulkan support as well as toggle it
    virtual bool setVulkan(const bool &enabled) = 0;
    //void setData();

    virtual bool initialize() = 0;
    virtual void draw() = 0;
    virtual QString pluginName() = 0;

    virtual void setSize(const int &width, const int &height) = 0;

    virtual ~VisualizrPlugin() {}
};

Q_DECLARE_INTERFACE(VisualizrPlugin, VisualizrPlugin_iid)

#endif // VISUALIZRPLUGIN

