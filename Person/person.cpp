#include "person.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
using namespace Web;
Person::Person(QStringView _name, QObject *parent) : m_name(_name.toString()), QObject(parent) {
  if (auto ret{m_person.insert(m_name, qMakePair(m_age, m_score))}; !ret->second) {
    qDebug() << " Construct m_person failed! ";
  }
}

Person::Person(QMap<QString, QPair<int, double>> &_person, QObject *parent) : m_person(_person), QObject(parent) {
  auto it = m_person.begin();
  auto key = it.key();
  auto [val1, val2] = it.value();

  m_name.push_back(key);
  m_age = val1;
  m_score = val2;
}

int Person::getAge(QStringView _name) {
  if (m_person.contains(_name.toString()))
    return m_person[_name.toString()].first;
  else
    return -1;
}

bool Person::setAge(QStringView _name, int _age) {

  if (!m_person.contains(_name.toString()))
    return false;

  int tmp = m_person[_name.toString()].first;

  if (tmp == _age)
    return false;
  else {
    m_person[_name.toString()].first = _age;
    emit ageChanged();
    return true;
  }
}

QT_END_NAMESPACE