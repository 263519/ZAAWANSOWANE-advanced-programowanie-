#ifndef CUBOID_HH
#define CUBOID_HH


#include "AbstractMobileObj.hh"
#include <string>


class Cuboid : public AbstractMobileObj {
private:
    Vector3D _position; ///< Aktualna pozycja prostopadłościanu
    double _roll;       ///< Kąt roll (OX) w stopniach
    double _pitch;      ///< Kąt pitch (OY) w stopniach
    double _yaw;        ///< Kąt yaw (OZ) w stopniach
    std::string _name;  ///< Nazwa prostopadłościanu

public:

    Cuboid();
    ~Cuboid() override {}

    double GetAng_Roll_deg() const override;
    double GetAng_Pitch_deg() const override;
    double GetAng_Yaw_deg() const override;

    void SetAng_Roll_deg(double Ang_Roll_deg) override;
    void SetAng_Pitch_deg(double Ang_Pitch_deg) override;
    void SetAng_Yaw_deg(double Ang_Yaw_deg) override;

    const Vector3D& GetPositoin_m() const override;
    void SetPosition_m(const Vector3D& rPos) override;

    void SetName(const char* sName) override;
    const std::string& GetName() const override;
};

#endif // CUBOID_HH
