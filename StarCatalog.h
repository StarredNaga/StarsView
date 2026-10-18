//
// Created by StarredNaga on 18.10.2026.
//

#ifndef STARSVIEW_STARCATALOG_H
#define STARSVIEW_STARCATALOG_H
#include <vector>

#include "Star.h"


class StarCatalog {

    public:
    StarCatalog();
    StarCatalog(const std::vector<Star> &stars);
    StarCatalog(const std::string &filename);

    const std::vector<Star>& getStars();

    void loadFromFile(const std::string &filename);

    void saveToFile(const std::string &filename);

    private:
    std::vector<Star> stars;
};


#endif //STARSVIEW_STARCATALOG_H
