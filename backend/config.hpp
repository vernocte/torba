#ifndef CONFIG_HPP
#define CONFIG_HPP

// qt library
#include <QSettings>
#include <QSize>

// # Config
class Config
{
    // ## private
private:

    // ### fields

    // #### data
    QSettings _data;

public:

    // ### constructors

    // #### default constructor
    explicit Config();

    // ### accessors

    /*
    #### set event setting visibility

    [val]: value
    */
    void event_setting(bool val);

    /*
    #### get event setting visibility

    [returns]: value
    */
    bool event_setting();

    /*
    #### set find mail setting visibility

    [val]: value
    */
    void find_mail(bool val);

    /*
    #### get find mail setting visibility

    [returns]: value
    */
    bool find_mail();

    /*
    #### set full screen

    [val]: value
    */
    void fullscreen(bool val);

    /*
    #### get full screen

    [returns]: value
    */
    bool fullscreen();

    /*
    #### set import database setting visibility

    [val]: value
    */
    void import_database(bool val);

    /*
    #### get import database setting visibility

    [returns]: value
    */
    bool import_database();

    /*
    #### set new database setting visibility

    [val]: value
    */
    void new_database(bool val);

    /*
    #### get new database setting visibility

    [returns]: value
    */
    bool new_database();

    /*
    #### set person setting visibility

    [val]: value
    */
    void person_settings(bool val);

    /*
    #### get person setting visibility

    [returns]: value
    */
    bool person_settings();

    /*
    #### set save setting visibility

    [val]: value
    */
    void save_widget(bool val);

    /*
    #### get save setting visibility

    [returns]: value
    */
    bool save_widget();

    /*
    #### set setting visibility

    [val]: value
    */
    void settings_visible(bool val);

    /*
    #### get setting visibility

    [returns]: value
    */
    bool settings_visible();

    /*
    #### set window position

    [val]: value
    */
    void position(QPoint val);

    /*
    #### get window position

    [returns]: value
    */
    QPoint position();

    /*
    #### set window size

    [val]: value
    */
    void size(QSize val);

    /*
    #### get window size

    [returns]: value
    */
    QSize size();



};

#endif // CONFIG_HPP
