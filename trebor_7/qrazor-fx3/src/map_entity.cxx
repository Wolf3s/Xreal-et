/// ============================================================================
/*
Copyright (C) 1997-2001 Id Software, Inc.
Copyright (C) 2003 Robert Beckebans <trebor_7@users.sourceforge.net>
Please see the file "AUTHORS" for a list of contributors

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
/// ============================================================================


/// includes ===================================================================
// system -------------------------------------------------------------------
// qrazor-fx ----------------------------------------------------------------
#include "map_local.h"

#include "common.h"
#include "vfs.h"

// xreal --------------------------------------------------------------------


std::vector<entity_t>	entities;

void	StripTrailing(char *e)
{
	char	*s;

	s = e + strlen(e)-1;
	while(s >= e && *s <= 32)
	{
		*s = 0;
		s--;
	}
}

/*
std::pair<std::string, std::string>	ParseEpair(char **data_p)
{
	
	epair_t	*e;

	e = malloc (sizeof(epair_t));
	memset (e, 0, sizeof(epair_t));
	
	if (strlen(token) >= MAX_KEY-1)
		Error ("ParseEpar: token too long");
	e->key = copystring(token);
	GetToken (false);
	if (strlen(token) >= MAX_VALUE-1)
		Error ("ParseEpar: token too long");
	e->value = copystring(token);

	// strip trailing spaces
	StripTrailing (e->key);
	StripTrailing (e->value);

	return e;
	
	std::pair<std::string, std::string>	epair;	
}
*/



bool	ParseEntity(char **data_p)
{
	entity_t	mapent;

	char*		token;
	
	std::string	key;
	std::string	value;
	

	token = Com_Parse(data_p, true);
	if(!token[0])
		return false;

	if(!X_strequal(token, "{"))
		Com_Error(ERR_FATAL, "ParseEntity: found '%s' instead of {", token);
	
	while(true)
	{
		token = Com_Parse(data_p);
		
		if(!token[0])
		{
			Com_Error(ERR_FATAL, "EOF without closing brace");
			return false;
		}
		
		if(!token[0] || X_strequal(token, "}"))
			break;
		
		key = token;
		
		token = Com_Parse(data_p);
		
		std::string value = token;
		
		if(!*data_p)
			Com_Error(ERR_FATAL, "ParseEntity: EOF without closing brace");

		if(token[0] == '}')
			Com_Error(ERR_FATAL, "ParseEntity: closing brace without data");
		
		
		mapent.epairs.insert(make_pair(key, value));
	};
	
	entities.push_back(mapent);
	
	return true;
}

/*
================
ParseEntities

Parses the dentdata string into entities
================
*/
void	ParseEntities()
{
	entities.clear();
	
	std::string entdata;
	for(unsigned int i=0; i<dentdata.size(); i++)
	{
		entdata += dentdata[i];
	}
	
	char *data_p = (char*) entdata.c_str();
	
	Com_Printf("ParseEntities:\n%s\n", entdata.c_str());

	while(ParseEntity(&data_p))
	{
	}
}


/*
================
UnparseEntities

Generates the dentdata string from all the entities
================
*/
void	UnparseEntities()
{
	std::string	entitystring;

	for(std::vector<entity_t>::const_iterator eir = entities.begin(); eir != entities.end(); eir++)
	{
		entitystring += "{\n";
				
		for(std::map<std::string, std::string>::const_iterator ir = (*eir).epairs.begin(); ir != (*eir).epairs.end(); ir++)
		{
			entitystring += '\"';
			entitystring += ir->first;	// key
			entitystring += '\"';
			
			entitystring += ' ';
		
			entitystring += '\"';
			entitystring += ir->second;	//value
			entitystring += '\"';
			
			entitystring += '\n';
		}

		
		entitystring += "}\n";
	}
	
	for(std::string::iterator ir = entitystring.begin(); ir != entitystring.end(); ir++)
	{
		dentdata.push_back(*ir);
	}
}

void	PrintEntity(entity_t &ent)
{
	Com_Printf("------- entity -------\n");
	
	for(std::map<std::string, std::string>::const_iterator ir = ent.epairs.begin(); ir != ent.epairs.end(); ir++)
	{
		Com_Printf("%s = %s\n", ir->first.c_str(), ir->second.c_str());
	}

}

void 	SetKeyValue(entity_t &ent, const std::string &key, const std::string &value)
{
	std::map<std::string, std::string>::iterator ir = ent.epairs.find(key);
			
	if(ir != ent.epairs.end())
	{
		ir->second = value;
	}
	else
	{
		ent.epairs.insert(make_pair(key, value));
	}
}

const char*	ValueForKey(entity_t &ent, const std::string &key)
{
	std::map<std::string, std::string>::iterator ir = ent.epairs.find(key);
			
	if(ir != ent.epairs.end())
	{
		return ir->second.c_str();
	}
	else
	{
		return "";
	}
}

vec_t	FloatForKey(entity_t &ent, const std::string &key)
{
	const char	*k;
	
	k = ValueForKey(ent, key);
	return atof(k);
}

void 	GetVector3ForKey(entity_t &ent, const std::string &key, vec3_c &v)
{
	const char	*k;
	double	v1, v2, v3;

	k = ValueForKey(ent, key);
	
	// scanf into doubles, then assign, so it is vec_t size independent
	v1 = v2 = v3 = 0;
	
	sscanf(k, "%lf %lf %lf", &v1, &v2, &v3);
	
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}



