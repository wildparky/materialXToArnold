#ifndef MTLX_TO_A_CONFIGURATION_H
#define MTLX_TO_A_CONFIGURATION_H

#include <string>

// Aggregates and encapsulates the user's desired configuration (from one or
// more sources for, e. g. the Arnold parameters) for one run of the MaterialX
// to Arnold procedural node.
struct Configuration
{
    std::string materialx_search_path_ {""};

    std::string materialx_file_name_ {""};

    // The MaterialX document's color management system. If not specified in the
    // MaterialX document, this stirng should be empty and Arnold's built-in
    // color manager should be used.
    std::string color_management_sysem_ {""};

    // The MaterialX document's working color space.
    //
    // The working color space of a MaterialX document is defined by the
    // colorspace attribute of its root <materialx> element, and it is strongly
    // recommended that all <materialx> elements define a specific colorspace
    // if they wish to use a color-managed workflow rather than relying on a
    // default colorspace

    //The color space of individual color image files and values may be defined via a colorspace attribute
    //in a parameter which defines a filename or value. Color images and values in spaces other than the
    //working space are expected to be transformed by the application into the working space before
    //computations are performed.

    // (the color space that input
    // was created in). This color space should be used when one is not provided
    // in MaterialX elements. If not specified, the should default to the
    // rendering color space in order to make sure the values are used as-is.
    std:: string working_color_space_ {""};


   const char* procedural_node_name_ {nullptr};

   void* user_data_ptr_ {nullptr};
};


#endif // MTLX_TO_A_CONFIGURATION_H
