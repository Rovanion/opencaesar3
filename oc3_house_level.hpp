// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com


#ifndef HOUSE_LEVEL_HPP
#define HOUSE_LEVEL_HPP

#include <string>
#include <map>
#include <list>
#include "oc3_enums.hpp"
#include "oc3_scopedptr.hpp"

class House;
class HouseLevelSpec
{
   friend class HouseSpecHelper;

public:
   int getHouseLevel();
   int getMaxHabitantsByTile();
   int getTaxRate();

   // return the house type "small casa, luxury villa, ..."
   std::string& getLevelName();

   // returns True if patrician villa
   bool isPatrician();

   bool checkHouse(House &house);

   int computeEntertainmentLevel(House &house);
   int computeEducationLevel(House &house, std::string &oMissingRequirement);
   int computeHealthLevel(House &house, std::string &oMissingRequirement);
   int computeReligionLevel(House &house);
   int computeWaterLevel(House &house, std::string &oMissingRequirement);
   int computeFoodLevel(House &house);
   int computeMonthlyConsumption(House &house, const GoodType goodType);

   float evaluateServiceNeed(House &house, const ServiceType service);
   float evaluateEntertainmentNeed(House &house, const ServiceType service);
   float evaluateEducationNeed(House &house, const ServiceType service);
   float evaluateHealthNeed(House &house, const ServiceType service);
   float evaluateReligionNeed(House &house, const ServiceType service);
   // float evaluateFoodNeed(House &house, const ServiceType service);


//    int getMinEntertainmentLevel();
//    int getMinEducationLevel();
//    int getMinHealthLevel();
//    int getMinReligionLevel();
//    int getMinWaterLevel();
//    int getMinFoodLevel();
  
private:
  int _houseLevel;
  int _maxHabitantsByTile;
  std::string _levelName;
  int _taxRate;

   // required services
  int _minEntertainmentLevel;
  int _minHealthLevel;
  int _midDesirability, _maxDesirability;
  int _minEducationLevel;
  int _crime;
  int _prosperity;
  int _minWaterLevel;  // access to water (no water=0, well=1, fountain=2)
  int _minReligionLevel;  // number of religions
  int _minFoodLevel;  // number of food types
  std::map<GoodType, int> _requiredGoods;  // rate of good usage for every good (furniture, pottery, ...)
};

class HouseSpecHelper
{
public:
  static HouseSpecHelper& getInstance();

  HouseLevelSpec &getHouseLevelSpec(const int houseLevel);
  void setHouseLevelSpec(HouseLevelSpec &spec);
  int getHouseLevel(const int houseId);
  void initialize( const std::string& filename );

  ~HouseSpecHelper();
private:
  HouseSpecHelper();
  
  class Impl;
  ScopedPtr< Impl > _d;
};


#endif
