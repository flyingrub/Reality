#include <QApplication>
#include <QQmlApplicationEngine>

#include <QDir>
#include <QDebug>
#include <QMovie>
#include <QLabel>


#include <string>
#include <iostream>
#include <vector>
#include <random>


using namespace std;

QStringList gifs;

random_device seeder;
mt19937 engine(seeder());
uniform_int_distribution<int> rand_dist;

void get_all_files()
{
    QDir dir = QDir::currentPath();
    bool res = dir.cd("../gif");
    gifs = dir.entryList(QDir::Files).filter(".gif");
    rand_dist = uniform_int_distribution<int>(0, gifs.size() - 1);
}

void debug_files() {
    for (int i = 0; i < gifs.size(); ++i)
        qDebug() << gifs.at(i);
}

int get_random_index() {
    return rand_dist(engine);
}

QString get_random_gif() {
    return gifs.at(get_random_index());
}

bool load_qt_app() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return engine.rootObjects().isEmpty();
}

int main(int argc, char *argv[])
{
    get_all_files();
    // debug_files();

    QApplication app(argc, argv);
    // if(load_qt_app()) return -1;

    QLabel label;
    QMovie *movie = new QMovie("gif/" + get_random_gif());
    movie->setFileName("gif/" + get_random_gif());

    label.setMovie(movie);
    movie->start();
    label.show();

    return app.exec();
}
