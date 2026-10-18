#include "StarCatalog.h"
#include <fstream>
#include <stdexcept>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

namespace sf {
    template<class Archive>
    void serialize(Archive& archive, sf::Vector3f& v) {
        archive(cereal::make_nvp("x", v.x),
                cereal::make_nvp("y", v.y),
                cereal::make_nvp("z", v.z));
    }
}

namespace cereal {
    template<class Archive>
    void save(Archive& archive, const Star& star) {

        int r = star.getColor().r;
        int g = star.getColor().g;
        int b = star.getColor().b;
        int a = star.getColor().a;

        archive(cereal::make_nvp("name", star.getName()),
                cereal::make_nvp("center", star.getCenter()),
                cereal::make_nvp("radius", star.getRadius()),
                cereal::make_nvp("r", r),
                cereal::make_nvp("g", g),
                cereal::make_nvp("b", b),
                cereal::make_nvp("a", a));
    }

    template<class Archive>
    void load(Archive& archive, Star& star) {
        std::string name;
        sf::Vector3f center;
        float radius;
        int r, g, b, a;

        archive(cereal::make_nvp("name", name),
                cereal::make_nvp("center", center),
                cereal::make_nvp("radius", radius),
                cereal::make_nvp("r", r),
                cereal::make_nvp("g", g),
                cereal::make_nvp("b", b),
                cereal::make_nvp("a", a));

        star = Star(name, center, radius, sf::Color(r, g, b, a));
    }
}

StarCatalog::StarCatalog() : stars{} {}

StarCatalog::StarCatalog(const std::vector<Star> &stars) {
    if (stars.empty()) throw std::invalid_argument("Empty StarCatalog");
    this->stars = stars;
}

StarCatalog::StarCatalog(const std::string &filename) {
    if (filename.empty()) throw std::invalid_argument("Incorrect file name");
    loadFromFile(filename);
}

const std::vector<Star>& StarCatalog::getStars() {
    return stars;
}

void StarCatalog::loadFromFile(const std::string &filename) {
    if (filename.empty()) throw std::invalid_argument("Incorrect file name");

    std::ifstream is(filename);
    if (!is.is_open()) throw std::runtime_error("Failed to open file: " + filename);

    cereal::JSONInputArchive archive(is);
    archive(cereal::make_nvp("stars", stars));
}

void StarCatalog::saveToFile(const std::string &filename) {
    if (filename.empty()) throw std::invalid_argument("Incorrect file name");

    std::ofstream os(filename);
    if (!os.is_open()) throw std::runtime_error("Failed to open file: " + filename);

    cereal::JSONOutputArchive archive(os);
    archive(cereal::make_nvp("stars", stars));
}
