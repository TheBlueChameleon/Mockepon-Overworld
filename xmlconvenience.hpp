#ifndef XMLCONVENIENCE_HPP
#define XMLCONVENIENCE_HPP

// ========================================================================== //
// Depenencies

// STL
#include <vector>
#include <string>

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

pugi::xml_document loadXML(const std::string & filename, const std::string & content = "");

const std::vector<std::string> & extractAnimationFrameList(pugi::xml_document & doc);

#endif // XMLCONVENIENCE_HPP
