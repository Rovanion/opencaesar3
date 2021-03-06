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

#include "oc3_well.hpp"
#include "oc3_resourcegroup.hpp"
#include "oc3_servicewalker.hpp"
#include "oc3_scenario.hpp"
#include "oc3_tile.hpp"

BuildingWell::BuildingWell() : ServiceBuilding(S_WELL, B_WELL, Size(1) )
{
  _fireIncrement = 0;
  _damageIncrement = 0;
}

void BuildingWell::deliverService()
{
  ServiceWalkerPtr walker = ServiceWalker::create( Scenario::instance().getCity(), getService() );
  walker->setBase( BuildingPtr( this ) );

  ServiceWalker::ReachedBuildings reachedBuildings = walker->getReachedBuildings( getTile().getIJ() );
  for( ServiceWalker::ReachedBuildings::iterator itBuilding = reachedBuildings.begin(); 
    itBuilding != reachedBuildings.end(); ++itBuilding)
  {
    (*itBuilding)->applyService( walker );
  }
}

char BuildingWell::getDesirabilityInfluence() const
{
  return -1;
}
