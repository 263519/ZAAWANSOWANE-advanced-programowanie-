#include "Cuboid.hh"


Cuboid::Cuboid() : _position(), _roll(0), _pitch(0), _yaw(0), _name("Unnamed Cuboid") {}


double Cuboid::GetAng_Roll_deg() const {
    return _roll;
}

double Cuboid::GetAng_Pitch_deg() const {
    return _pitch;
}


double Cuboid::GetAng_Yaw_deg() const {
    return _yaw;
}


void Cuboid::SetAng_Roll_deg(double Ang_Roll_deg) {
    _roll = Ang_Roll_deg;
}


void Cuboid::SetAng_Pitch_deg(double Ang_Pitch_deg) {
    _pitch = Ang_Pitch_deg;
}



void Cuboid::SetAng_Yaw_deg(double Ang_Yaw_deg) {
    _yaw = Ang_Yaw_deg;
}


const Vector3D& Cuboid::GetPositoin_m() const {
    return _position;
}


void Cuboid::SetPosition_m(const Vector3D& rPos) {
    _position = rPos;
}


void Cuboid::SetName(const char* sName) {
    _name = sName;
}

/*!
 * \brief Udostępnia nazwę prostopadłościanu.
 * \return Nazwa obiektu jako string.
 */
const std::string& Cuboid::GetName() const {
    return _name;
}
