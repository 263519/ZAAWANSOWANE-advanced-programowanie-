#ifndef CUBOID_HH
#define CUBOID_HH

#include "AbstractMobileObj.hh"
#include "Vector3D.hh"
#include "geomVector.hh"
#include <string>

class Cuboid : public AbstractMobileObj {
private:
    Vector3D _position;
    Vector3D _shift;
    Vector3D _scale;
    Vector3D _rotation;
    Vector3D _translation;
    Vector3D _rgb;
    double _roll;
    double _pitch;
    double _yaw;
    std::string _name;

public:
    Cuboid();
    Cuboid(const Vector3D &position, const Vector3D &shift, const Vector3D &scale,
           const Vector3D &rotation, const Vector3D &translation, const Vector3D &rgb,
           double roll, double pitch, double yaw, const std::string &name);

    virtual ~Cuboid();

    double GetAng_Roll_deg() const override;
    double GetAng_Pitch_deg() const override;
    double GetAng_Yaw_deg() const override;

    void SetAng_Roll_deg(double Ang_Roll_deg) override;
    void SetAng_Pitch_deg(double Ang_Pitch_deg) override;
    void SetAng_Yaw_deg(double Ang_Yaw_deg) override;

    const Vector3D & GetPositoin_m() const override;
    void SetPosition_m(const Vector3D &rPos) override;

    void SetName(const char* sName) override;
    const std::string & GetName() const override;

    const Vector3D & GetShift() const;
    void SetShift(const Vector3D &shift);

    const Vector3D & GetScale() const;
    void SetScale(const Vector3D &scale);

    const Vector3D & GetRotation() const;
    void SetRotation(const Vector3D &rotation);

    const Vector3D & GetTranslation() const;
    void SetTranslation(const Vector3D &translation);

    const Vector3D & GetRGB() const;
    void SetRGB(const Vector3D &rgb);
};

#endif
