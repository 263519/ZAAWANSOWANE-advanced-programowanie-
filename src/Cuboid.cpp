#include "Cuboid.hh"

Cuboid::Cuboid(){}

Cuboid::Cuboid(const Vector3D &position, const Vector3D &shift, const Vector3D &scale,
               const Vector3D &rotation, const Vector3D &translation, const Vector3D &rgb,
               double roll, double pitch, double yaw, const std::string &name)
    : _position(position), _shift(shift), _scale(scale), _rotation(rotation),
      _translation(translation), _rgb(rgb), _roll(roll), _pitch(pitch), _yaw(yaw), _name(name) {}

Cuboid::~Cuboid() {}

double Cuboid::GetAng_Roll_deg() const { return _roll; }
double Cuboid::GetAng_Pitch_deg() const { return _pitch; }
double Cuboid::GetAng_Yaw_deg() const { return _yaw; }

void Cuboid::SetAng_Roll_deg(double Ang_Roll_deg) { _roll = Ang_Roll_deg; }
void Cuboid::SetAng_Pitch_deg(double Ang_Pitch_deg) { _pitch = Ang_Pitch_deg; }
void Cuboid::SetAng_Yaw_deg(double Ang_Yaw_deg) { _yaw = Ang_Yaw_deg; }

const Vector3D & Cuboid::GetPositoin_m() const { return _position; }
void Cuboid::SetPosition_m(const Vector3D &rPos) { _position = rPos; }

void Cuboid::SetName(const char* sName) { _name = sName; }
const std::string & Cuboid::GetName() const { return _name; }

const Vector3D & Cuboid::GetShift() const { return _shift; }
void Cuboid::SetShift(const Vector3D &shift) { _shift = shift; }

const Vector3D & Cuboid::GetScale() const { return _scale; }
void Cuboid::SetScale(const Vector3D &scale) { _scale = scale; }

const Vector3D & Cuboid::GetRotation() const { return _rotation; }
void Cuboid::SetRotation(const Vector3D &rotation) { _rotation = rotation; }

const Vector3D & Cuboid::GetTranslation() const { return _translation; }
void Cuboid::SetTranslation(const Vector3D &translation) { _translation = translation; }

const Vector3D & Cuboid::GetRGB() const { return _rgb; }
void Cuboid::SetRGB(const Vector3D &rgb) { _rgb = rgb; }
