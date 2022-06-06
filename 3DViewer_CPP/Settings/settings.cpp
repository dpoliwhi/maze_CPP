#include "settings.h"

namespace s21 {

Settings::Settings()
    : bgColor(0.0, 0.0, 0.0, 0.0), edgeColor(0.0, 0.0, 0.0, 0.0), vertexColor(0.0, 0.0, 0.0, 0.0) {
  lineWidth = 0.0;
  pointSize = 0.0;
  lineType = 0;
  pointType = 0;
  projection = 0;
}

void Settings::getSettingFromFile() {
  QFile file(HOME_DIR "Resources/settings.conf");
  QString fileData, buf;
  if (!file.open(QFile::ReadOnly)) {
    qDebug() << "Where is settings.conf file?";
  } else {
    QTextStream in(&file);
    while (!in.atEnd()) {
      in >> buf;
      fileData.append(buf);
      fileData.append(" ");
    }
    if (fileData.toStdString() != "#000000 #ffffff #ffffff 1 0 0 0 0 ") {
      QMessageBox::information(NULL, QObject::tr("Информация"),
                               "Attention!\n\nCustom settings will be loaded\nClick RESET SETTINGS if you "
                               "want to restore the basic settings");
    }

    QStringList data = fileData.split(' ');

    bgColor = data[0];
    edgeColor = data[1];
    vertexColor = data[2];
    lineWidth = data[3].toDouble();
    pointSize = data[4].toDouble();
    lineType = data[5].toInt();
    pointType = data[6].toInt();
    projection = data[7].toInt();

    file.close();
  }
}

void Settings::setSettingToFile() {
  QFile file(HOME_DIR "Resources/settings.conf");
  if (!file.open(QFile::WriteOnly)) {
    qDebug() << "Where is settings.conf file?";
  } else {
    QTextStream in(&file);
    in << bgColor.name() << "\n";
    in << edgeColor.name() << "\n";
    in << vertexColor.name() << "\n";
    in << lineWidth << "\n";
    in << pointSize << "\n";
    in << lineType << "\n";
    in << pointType << "\n";
    in << projection;
  }
  file.close();
}

void Settings::setDefaultSetting() {
  bgColor = "#000000";
  edgeColor = {255, 255, 255};
  vertexColor = {255, 255, 255};
  lineType = 0;
  lineWidth = 1.0;
  pointType = 0;
  pointSize = 0.0;
  projection = 0;
}
}  // namespace s21
