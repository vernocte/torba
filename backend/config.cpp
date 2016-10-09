#include "config.hpp"

#include<QPoint>

// ### constructors

// #### default constructor
Config::Config() : _data("Vernocte laboratories", "DB manager") { }

// ### accessors

/*
#### set event setting visibility

[val]: value
*/
void Config::event_setting(const bool val)
{
    _data.setValue("event_setting", val);
}

/*
#### get event setting visibility

[returns]: value
*/
bool Config::event_setting()
{
    return _data.value("event_setting").value<bool>();
}

/*
#### set find mail setting visibility

[val]: value
*/
void Config::find_mail(const bool val)
{
    _data.setValue("find_mail", val);
}

/*
#### get find mail setting visibility

[returns]: value
*/
bool Config::find_mail()
{
    return _data.value("find_mail").value<bool>();
}

/*
#### set full screen

[val]: value
*/
void Config::fullscreen(const bool val)
{
    _data.setValue("fullscreen", val);
}

/*
#### get full screen

[returns]: value
*/
bool Config::fullscreen()
{
    return _data.value("fullscreen").value<bool>();
}

/*
#### set import database setting visibility

[val]: value
*/
void Config::import_database(const bool val)
{
    _data.setValue("import_database", val);
}

/*
#### get import database setting visibility

[returns]: value
*/
bool Config::import_database()
{
    return _data.value("import_database").value<bool>();
}

/*
#### set new database setting visibility

[val]: value
*/
void Config::new_database(const bool val)
{
    _data.setValue("new_database", val);
}

/*
#### get new database setting visibility

[returns]: value
*/
bool Config::new_database()
{
    return _data.value("new_database").value<bool>();
}

/*
#### set person setting visibility

[val]: value
*/
void Config::person_settings(const bool val)
{
    _data.setValue("person_settings", val);
}

/*
#### get person setting visibility

[returns]: value
*/
bool Config::person_settings()
{
    return _data.value("person_settings").value<bool>();
}

/*
#### set save setting visibility

[val]: value
*/
void Config::save_widget(const bool val)
{
    _data.setValue("save_widget", val);
}

/*
#### get save setting visibility

[returns]: value
*/
bool Config::save_widget()
{
    return _data.value("save_widget").value<bool>();
}

/*
#### set setting visibility

[val]: value
*/
void Config::settings_visible(const bool val)
{
    _data.setValue("settings_visible", val);
}

/*
#### get setting visibility

[returns]: value
*/
bool Config::settings_visible()
{
    return _data.value("settings_visible").value<bool>();
}

/*
#### set window position

[val]: value
*/
void Config::position(const QPoint& val)
{
    _data.setValue("position", val);
}

/*
#### get window position

[returns]: value
*/
QPoint Config::position()
{
    return _data.value("position").value<QPoint>();
}

/*
#### set window size

[val]: value
*/
void Config::size(const QSize& val)
{
    _data.setValue("size", val);
}

/*
#### get window size

[returns]: value
*/
QSize Config::size()
{
    return _data.value("size").value<QSize>();
}

/*
#### set last path

[val]: value
*/
void Config::last_path(const QString& val)
{
    _data.setValue("last path", val);
}

/*
#### get window size

[returns]: value
*/
QString Config::last_path()
{
    return _data.value("last path").value<QString>();
}
