#ifndef XMLCONVENIENCE_HPP
#define XMLCONVENIENCE_HPP

// ========================================================================== //
// Depenencies

// STL
#include <vector>
#include <string>
#include <utility>

// PUGI
#include "pugixml.hpp"

// local

// ========================================================================== //
// project version

#define PROJECT_NAME "Mockepon"
#define VERSION_MAJOR 1
#define VERSION_MINOR 1

// ========================================================================== //
// proc

pugi::xml_document XMLload(const std::string & filename, const std::string & content = "");

std::vector<
    std::pair<std::string,
              std::vector<std::pair<std::string, std::string>>
    >
> XMLextractAttributeList (pugi::xml_node & node);

#endif // XMLCONVENIENCE_HPP
