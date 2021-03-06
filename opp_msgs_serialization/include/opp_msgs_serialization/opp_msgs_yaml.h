/*
 * Copyright 2019 Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OPP_MSGS_SERIALIZATION_OPP_MSGS_YAML_H
#define OPP_MSGS_SERIALIZATION_OPP_MSGS_YAML_H

#include <noether_msgs/ToolPathConfig.h>

#include <opp_msgs/Job.h>
#include <opp_msgs/ToolPath.h>
#include <opp_msgs/TouchPoint.h>
#include "opp_msgs_serialization/geometry_msgs_yaml.h"
#include "opp_msgs_serialization/sensor_msgs_yaml.h"

namespace YAML
{
template <>
struct convert<noether_msgs::ToolPathConfig>
{
  static Node encode(const noether_msgs::ToolPathConfig& rhs)
  {
    Node node;
    node["pt_spacing"] = rhs.pt_spacing;
    node["line_spacing"] = rhs.line_spacing;
    node["tool_offset"] = rhs.tool_offset;
    node["intersecting_plane_height"] = rhs.intersecting_plane_height;
    node["min_hole_size"] = rhs.min_hole_size;
    node["min_segment_size"] = rhs.min_segment_size;
    node["raster_angle"] = rhs.raster_angle;
    node["raster_wrt_global_axes"] = rhs.raster_wrt_global_axes;
    node["generate_extra_rasters"] = rhs.generate_extra_rasters;
    return node;
  }

  static bool decode(const Node& node, noether_msgs::ToolPathConfig& rhs)
  {
    if (node.size() != 9)
      return false;
    rhs.pt_spacing = node["pt_spacing"].as<decltype(rhs.pt_spacing)>();
    rhs.line_spacing = node["line_spacing"].as<decltype(rhs.line_spacing)>();
    rhs.tool_offset = node["tool_offset"].as<decltype(rhs.tool_offset)>();
    rhs.intersecting_plane_height = node["intersecting_plane_height"].as<decltype(rhs.intersecting_plane_height)>();
    rhs.min_hole_size = node["min_hole_size"].as<decltype(rhs.min_hole_size)>();
    rhs.min_segment_size = node["min_segment_size"].as<decltype(rhs.min_segment_size)>();
    rhs.raster_angle = node["raster_angle"].as<decltype(rhs.raster_angle)>();
    rhs.raster_wrt_global_axes = node["raster_wrt_global_axes"].as<decltype(rhs.raster_wrt_global_axes)>();
    rhs.generate_extra_rasters = node["generate_extra_rasters"].as<decltype(rhs.generate_extra_rasters)>();
    return true;
  }
};

template <>
struct convert<opp_msgs::Job>
{
  static Node encode(const opp_msgs::Job& rhs)
  {
    Node node;
    node["header"] = rhs.header;
    node["id"] = rhs.id;
    node["name"] = rhs.name;
    node["description"] = rhs.description;
    node["part_id"] = rhs.part_id;
    node["paths"] = rhs.paths;
    return node;
  }

  static bool decode(const Node& node, opp_msgs::Job& rhs)
  {
    if (node.size() != 6)
      return false;
    rhs.header = node["header"].as<decltype(rhs.header)>();
    rhs.id = node["id"].as<decltype(rhs.id)>();
    rhs.name = node["name"].as<decltype(rhs.name)>();
    rhs.description = node["description"].as<decltype(rhs.description)>();
    rhs.part_id = node["part_id"].as<decltype(rhs.part_id)>();
    rhs.paths = node["paths"].as<decltype(rhs.paths)>();
    return true;
  }
};

template <>
struct convert<opp_msgs::ProcessType>
{
  static Node encode(const opp_msgs::ProcessType& rhs)
  {
    Node node;
    node["val"] = rhs.val;
    return node;
  }

  static bool decode(const Node& node, opp_msgs::ProcessType& rhs)
  {
    if (node.size() != 1)
      return false;
    rhs.val = node["val"].as<decltype(rhs.val)>();
    return true;
  }
};

template <>
struct convert<opp_msgs::ToolPath>
{
  static Node encode(const opp_msgs::ToolPath& rhs)
  {
    Node node;
    node["header"] = rhs.header;
    node["process_type"] = rhs.process_type;
    node["paths"] = rhs.paths;
    node["dwell_time"] = rhs.dwell_time;
    node["tool_offset"] = rhs.tool_offset;
    node["params"] = rhs.params;
    return node;
  }

  static bool decode(const Node& node, opp_msgs::ToolPath& rhs)
  {
    // Allow both old entries (without Noether params) and new entries (with Noether params)
    if (node.size() != 5 && node.size() != 6)
      return false;

    // Get the opp_msgs::ToolPath fields
    rhs.header = node["header"].as<decltype(rhs.header)>();
    rhs.process_type = node["process_type"].as<decltype(rhs.process_type)>();
    rhs.paths = node["paths"].as<decltype(rhs.paths)>();
    rhs.dwell_time = node["dwell_time"].as<decltype(rhs.dwell_time)>();
    rhs.tool_offset = node["tool_offset"].as<decltype(rhs.tool_offset)>();

    // Get the Noether parameters, if they exist
    if (node["params"])
    {
      rhs.params = node["params"].as<decltype(rhs.params)>();
    }
    return true;
  }
};

template <>
struct convert<opp_msgs::ToolPathParams>
{
  static Node encode(const opp_msgs::ToolPathParams& rhs)
  {
    Node node;
    // Do the things inside the noether_msgs::ToolPathConfig
    node["config"] = rhs.config;
    node["curvature_threshold"] = rhs.curvature_threshold;
    node["min_polygons_per_cluster"] = rhs.min_polygons_per_cluster;
    return node;
  }

  static bool decode(const Node& node, opp_msgs::ToolPathParams& rhs)
  {
    if (node.size() != 3)
    {
      return false;
    }
    rhs.config = node["config"].as<decltype(rhs.config)>();
    rhs.curvature_threshold = node["curvature_threshold"].as<decltype(rhs.curvature_threshold)>();
    rhs.min_polygons_per_cluster = node["min_polygons_per_cluster"].as<decltype(rhs.min_polygons_per_cluster)>();
    return true;
  }
};

template <>
struct convert<opp_msgs::TouchPoint>
{
  static Node encode(const opp_msgs::TouchPoint& rhs)
  {
    Node node;
    node["name"] = rhs.name;
    node["description"] = rhs.description;
    node["threshold"] = rhs.threshold;
    node["transform"] = rhs.transform;
    return node;
  }

  static bool decode(const Node& node, opp_msgs::TouchPoint& rhs)
  {
    if (node.size() != 4)
      return false;
    rhs.name = node["name"].as<decltype(rhs.name)>();
    rhs.description = node["description"].as<decltype(rhs.description)>();
    rhs.threshold = node["threshold"].as<decltype(rhs.threshold)>();
    rhs.transform = node["transform"].as<decltype(rhs.transform)>();
    return true;
  }
};

}  // namespace YAML

#endif  // OPP_MSGS_SERIALIZATION_OPP_MSGS_YAML_H
