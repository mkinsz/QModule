import os

def newProject(name):
    try:
        os.mkdir( "../plugins/"+name, 0o755 ); 
    except IOError:
        print('Project Existence')

def newProfile(name):
    try:
        fobj=open("../plugins/"+name+'/'+name + '.pro',"a")
    except IOError:
        print('New Project Error:')
    else:
        fobj.write('#------------------------------------------------- \n'
        '# \n'
        '# Project created by Script \n'
        '# \n'
        '#------------------------------------------------- \n\n'
        'QT += widgets \n\n'
        'TARGET = '+lower(name)+'\n'
        'TEMPLATE = lib \n\n'
        'CONFIG += c++11 \n\n'
        'DEFINES += '+upper(name)+'_LIBRARY \n\n'
        'include(../build_plugins.pri) \n\n'
        'SOURCES += \\\n'
        '   '+lower(name)+'.cpp\\\n'
        '   form.cpp\n\n'
        'HEADERS += \\\n'
        '   '+lower(name)+'_global.h \\\n'
        '   '+lower(name) +'.h \\\n'
        '   form.h\n\n')
        fobj.close()

def pluginJSON(name):
    try:
        fobj=open("../plugins/"+name+'/'+lower(name)+'.json',"a")
    except IOError:
        print('New global_h Erro:')
    else:
        fobj.write('{}')
        fobj.close()

def globalHpp(name):
    try:
        fobj=open("../plugins/"+name+'/'+lower(name)+'_global.h',"a")
    except IOError:
        print('New global_h Erro:')
    else:
        fobj.write('#ifndef '+upper(name)+'_GLOBAL_H \n'
        '#define  '+upper(name)+'_GLOBAL_H \n\n'
        '#include <QtCore/qglobal.h>\n\n'
        '#if defined('+upper(name)+'_LIBRARY)\n'
        '#  define '+upper(name)+'SHARED_EXPORT Q_DECL_EXPORT\n'
        '#else\n'
        '#  define '+upper(name)+'SHARED_EXPORT Q_DECL_IMPORT\n'
        '#endif\n\n'
        '#endif // '+upper(name)+'_GLOBAL_H')
        fobj.close()

def pluginHpp(name):
    try:
        fobj=open("../plugins/"+name+'/'+lower(name)+'.h',"a")
    except IOError:
        print('New plugin_h Error:')
    else:
        fobj.write('#ifndef '+upper(name)+'_H \n'
        '#define '+upper(name)+'_H \n\n'
        '#define BrushInterface_iid "org.MK.FramewareAndPlugin.UnitInterface"\n\n'
        '#include "'+lower(name)+'_global.h"\n'
        '#include "../../apps/interfaces.h"\n'
        '#include <QObject>\n'
        '#include <QWidget>\n\n'
        'class '+upper(name)+'SHARED_EXPORT '+name+':public QObject,UnitInterface\n'
        '{\n'
        '   Q_OBJECT\n'
        '   Q_PLUGIN_METADATA(IID UnitInterface_iid FILE "'+lower(name)+'.json")\n'
        '   Q_INTERFACES(UnitInterface)\n\n'
        'public:\n'
        '     QString name() const;\n'
        '     QString iconPath() const;\n'
        '     QWidget *widget() const;\n'
        '     UNIT_TYPE unitType() const;\n'
        '     Qt::DockWidgetArea dockArea() const;\n'
        '};\n'
        '#endif // TESTPLUGIN_H')
        fobj.close()

def pluginCpp(name):
    try:
        fobj=open("../plugins/"+name+'/'+lower(name)+'.cpp',"a")
    except IOError:
        print('New plugin_cpp Error:')
    else:
        fobj.write('#include "'+lower(name)+'.h" \n'
        '#include "form.h"\n\n'
        'QString '+name+'::name() const\n'
        '{\n'
        '    return tr("'+name+'");\n'
        '}\n\n'
        'QString '+name+'::iconPath() const\n'
        '{\n'
        '   return ":/res/'+lower(name)+'.ico";\n'
        '}\n\n'
        'QWidget *'+name+'::widget() const\n'
        '{\n'
        '    return new Form();\n'
        '}\n\n'
        'UNIT_TYPE '+name+'::unitType() const\n'
        '{\n'
        '   return UNIT_TYPE::MDIAREA;\n'
        '}\n\n'
        'Qt::DockWidgetArea '+name+'::dockArea() const\n'
        '{\n'
        '   return Qt::LeftDockWidgetArea;\n'
        '}')
        fobj.close()

def formHpp(name):
    try:
        fobj=open("../plugins/"+name+'/form.h',"a")
    except IOError:
        print('New form_h Error:')
    else:
        fobj.write('#ifndef FORM_H \n'
        '#define FORM_H\n\n'
        '#include <QWidget>\n\n'
        'class Form : public QWidget\n'
        '{\n'
        '    Q_OBJECT\n\n'
        'public:\n'
        '    explicit Form(QWidget *parent = 0);\n'
        '    ~Form();\n\n'
        '};\n\n'
        '#endif // FORM_H')
        fobj.close()

def formCpp(name):
    try:
        fobj=open("../plugins/"+name+'/form.cpp',"a")
    except IOError:
        print('New form_CPP Error:')
    else:
        fobj.write('#include "form.h"\n\n'
        'Form::Form(QWidget *parent) :\n'
        '   QWidget(parent)\n'
        '{\n\n'
        '}\n\n'
        'Form::~Form()\n'
        '{\n\n'
        '}')
        fobj.close()

def upper(inStr):
    return inStr.upper()

def lower(inStr):
    return inStr.lower()

if __name__=="__main__":
    name=input('Enter Project Name:')
    newProject(name)
    newProfile(name)
    pluginJSON(name)
    globalHpp(name)
    pluginHpp(name)
    pluginCpp(name)
    formHpp(name)
    formCpp(name)