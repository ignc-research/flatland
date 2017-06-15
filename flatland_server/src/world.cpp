/*
 *  ______                   __  __              __
 * /\  _  \           __    /\ \/\ \            /\ \__
 * \ \ \L\ \  __  __ /\_\   \_\ \ \ \____    ___\ \ ,_\   ____
 *  \ \  __ \/\ \/\ \\/\ \  /'_` \ \ '__`\  / __`\ \ \/  /',__\
 *   \ \ \/\ \ \ \_/ |\ \ \/\ \L\ \ \ \L\ \/\ \L\ \ \ \_/\__, `\
 *    \ \_\ \_\ \___/  \ \_\ \___,_\ \_,__/\ \____/\ \__\/\____/
 *     \/_/\/_/\/__/    \/_/\/__,_ /\/___/  \/___/  \/__/\/___/
 * @copyright Copyright 2017 Avidbots Corp.
 * @name	 world.cpp
 * @brief	 Loads world file
 * @author Joseph Duchesne
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2017, Avidbots Corp.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Avidbots Corp. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include <ros/ros.h>
#include <string>
#include <yaml-cpp/yaml.h>
#include <map>
#include <flatland_server/world.h>
#include <boost/filesystem.hpp>


#include "flatland_server/world.h"

namespace flatland_server {

World::World(std::string world_file, b2World *physics_world)
    : physics_world_(physics_world) {
  ROS_INFO_NAMED("World", "World loaded");
}

bool World::load_world(std::string yaml_path) {

  // parse the world YAML file
  YAML::Node yaml = YAML::LoadFile(yaml_path);

  if (yaml["properties"] && yaml["properties"].IsMap()) {
    // TODO
  }
  else {
    return false;
  }

  std::vector<Layer> loaded_layers;
  if (yaml["layers"] && yaml["layers"].IsMap()) {
    auto layers = yaml["layers"];

    for (YAML::const_iterator it = yaml["layers"].begin();
      it != yaml["layers"].end(); ++it){

      Layer layer;

      layer.name = it->first.as<std::string>();

      boost::filesystem::path path(yaml_path);
      layer.load(path.parent_path(), it->second);

      loaded_layers.push_back(layer);
    }
  }
  else {
    return false;
  }

  if (yaml["models"] && yaml["models"].IsSequence()) {
    // TODO
  } else {
    return false;
  }

  layers_ = loaded_layers;
  return true;
}

};  // namespace flatland_server
