/// ============================================================================
/*
Copyright (C) 1997-2001 Id Software, Inc.
Copyright (C) 2003 Robert Beckebans <trebor_7@users.sourceforge.net>
Copyright (C) 2003, 2004  contributors of the XreaL project
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
// xreal --------------------------------------------------------------------
#include "cg_local.h"


void	CG_CheckPredictionError()
{
#if 0
	int		frame;
	vec3_c		delta;

	if(!cg_predict->value || (cgi.cl->frame.playerstate.pmove.pm_flags & PMF_NO_PREDICTION))
		return;

	// calculate the last usercmd_t we sent that the server has processed
	frame = cgi.cls->netchan.getIncomingAcknowledged();
	frame &= (CMD_BACKUP-1);

	// compare what the server returned with what we had predicted it to be
	delta = cgi.cl->frame.playerstate.pmove.origin - cgi.cl->predicted_origins[frame];

	// save the prediction error for interpolation
	if(fabs(delta[0]) > 128*8 || fabs(delta[1]) > 128*8 || fabs(delta[2]) > 128*8)
	{	
		// a teleport or something
		cgi.cl->prediction_error.clear();
	}
	else
	{
		if(cg_showmiss->value && (delta[0] || delta[1] || delta[2]))
			Com_Printf("prediction miss on %i: %i\n", cgi.cl->frame.serverframe, delta[0] + delta[1] + delta[2]);

		cgi.cl->predicted_origins[frame] = cgi.cl->frame.playerstate.pmove.origin;

		// save for error interpolation
		cgi.cl->prediction_error = delta * 0.125;
	}
#endif
}

/*
static void	CG_ClipMoveToEntities(const vec3_c &start, const cbbox_c &bbox, const vec3_c &end, trace_t *tr, int contentmask, int ignore)
{
	int			i, x, zd, zu;
	trace_t		trace;
	int			headnode;
	vec_t		*angles;
	entity_c	*ent;
	int			num;
	cmodel_t		*cmodel;
	
	cbbox_c	bbox2;

	for(i=0; i<cgi.cl->frame.entities_num; i++)
	{
		num = (cgi.cl->frame.entities_parse_index + i)&(MAX_PARSE_ENTITIES-1);
		ent = &cg.entities_parse[num];

		if(!ent->_s.solid)
			continue;

		if(ent->_s.getNumber() == ignore)
			continue;

		if(ent->_s.solid == 31)
		{	
			// special value for bmodel
			cmodel = cgi.cl->model_clip[ent->_s.modelindex];
			
			if (!cmodel)
				continue;
				
			headnode = cmodel->headnode;
			angles = ent->_s.angles;
		}
		else
		{	
			// encoded bbox
			x  = 8*( ent->_s.solid & 31);
			zd = 8*((ent->_s.solid>>5) & 31);
			zu = 8*((ent->_s.solid>>10) & 63) - 32;

			bbox2._mins[0] = bbox2._mins[1] = -x;
			bbox2._maxs[0] = bbox2._maxs[1] = x;
	
			bbox2._mins[2] = -zd;
			bbox2._maxs[2] =  zu;

			headnode = cgi.CM_HeadnodeForBox(bbox2);
			angles = vec3_origin;	// boxes don't rotate
		}

		if (tr->allsolid)
			return;

		trace = cgi.CM_TransformedBoxTrace (start, end, bbox, headnode, contentmask, ent->_s.origin, angles);

		if (trace.allsolid || trace.startsolid || trace.fraction < tr->fraction)
		{
			trace.ent = ent;
				
		 	if (tr->startsolid)
			{
				*tr = trace;
				tr->startsolid = true;
			}
			else
				*tr = trace;
		}
		else if (trace.startsolid)
			tr->startsolid = true;
	}
}
*/

/*
trace_t	CG_Trace(const vec3_c &start, const cbbox_c &bbox, const vec3_c &end, int contentmask, int ignore)
{
	trace_t	t;

	// check against world
	t = cgi.CM_BoxTrace(start, end, bbox, 0, contentmask);
	
	if(t.fraction < 1.0)
	{
		t.ent = (entity_c*)1;
		//Com_Printf("CG_Trace: t.fraction < 1.0\n");
	}

	// check all other solid models
	CG_ClipMoveToEntities(start, bbox, end, &t, contentmask, ignore);

	return t;
}
*/

/*
static trace_t	CG_PMTrace(const vec3_c &start, const cbbox_c &bbox, const vec3_c &end)
{
	return CG_Trace(start, bbox, end, MASK_PLAYERSOLID, IGNORE_PLAYER);
}
*/

/*
static int	CG_PMpointcontents(const vec3_c &point)
{
	int			i;
	
	entity_c*	ent_state;
	int		ent_num;
	
	cmodel_t	*cmodel;
	int		contents;

	contents = cgi.CM_PointContents(point, 0);


	for(i=0; i<cgi.cl->frame.entities_num; i++)
	{
		ent_num = (cgi.cl->frame.entities_parse_index + i) & (MAX_PARSE_ENTITIES-1);
		ent_state = &cg.entities_parse[ent_num];

		if(ent_state->_s.solid != 31) // special value for bmodel
			continue;

		cmodel = cgi.cl->model_clip[ent_state->_s.modelindex];
		
		if(!cmodel)
			continue;

		contents |= cgi.CM_TransformedPointContents(point, cmodel->headnode, ent_state->_s.origin, ent_state->_s.angles);
	}

	return contents;
}
*/

/*
cl.predicted_origin[0] = cl.frame.playerstate.pmove.origin[0];
cl.predicted_origin[1] = cl.frame.playerstate.pmove.origin[1];
cl.predicted_origin[2] = cl.frame.playerstate.pmove.origin[2];
			
cl.predicted_angles = cl.frame.playerstate.view_angles;
*/

void	CG_PredictMovement()
{
#if 0
	int			ack, current;
	int			frame;
	int			oldframe;
	usercmd_t	*cmd;
	pmove_t		pm;
	int			step;
	float			step_old;
	int			oldz;

	if(cgi.cls->state != CA_ACTIVE)
		return;
		
	if(!cg_predict->value || (cgi.cl->frame.playerstate.pmove.pm_flags & PMF_NO_PREDICTION))
	{	
		// just set angles
		cgi.cl->predicted_angles = cgi.cl->viewangles + cgi.cl->frame.playerstate.pmove.delta_angles;
		return;
	}

	ack = cgi.cls->netchan.getIncomingAcknowledged();
	current = cgi.cls->netchan.getOutgoingSequence();

	// if we are too far out of date, just freeze
	if(current - ack >= CMD_BACKUP)
	{
		if(cg_showmiss->value)
			Com_Printf("exceeded CMD_BACKUP\n");
		return;	
	}

	// copy current state to pmove
	memset(&pm, 0, sizeof(pm));
	pm.trace = CG_PMTrace;
	pm.pointcontents = CG_PMpointcontents;
	//pm_airaccelerate = atof(cgi.cl->configstrings[CS_AIRACCEL]);	//FIXME
	pm.s = cgi.cl->frame.playerstate.pmove;

	// run frames
	while(++ack < current)
	{
		frame = ack & (CMD_BACKUP-1);
		cmd = &cgi.cl->cmds[frame];

		pm.cmd = *cmd;
		cgi.Com_Pmove(&pm);

		// save for debug checking
		cgi.cl->predicted_origins[frame] = pm.s.origin;
	}

	oldframe = (ack-2) & (CMD_BACKUP-1);
	oldz = (int)cgi.cl->predicted_origins[oldframe][2];
	step = (int)(pm.s.origin[2] - oldz);
	
	if(step > 63 && step < 160 && (pm.s.pm_flags & PMF_ON_GROUND))
	{
		step_old = 0;
		
		//if(cgi.cls->realtime - cgi.cl->predicted_step_time < 150)
		//	step_old = cgi.cl->predicted_step_time * (150 - (cgi.cls->realtime - cgi.cl->predicted_step_time)) * (1.0/150);
		
		cgi.cl->predicted_step = step_old + step;
		cgi.cl->predicted_step_time = (int)(cgi.cls->realtime - cgi.cls->frametime / 2);
	}


	// copy results out for rendering
	cgi.cl->predicted_origin = pm.s.origin;

	cgi.cl->predicted_angles = pm.viewangles;
#else
	usercmd_t cmd;
	
	cgi.CL_GetCurrentUserCommand(cmd);

	// just set angles
	cg.predicted_angles = cmd.angles + cg.frame.playerstate.pmove.delta_angles;
	return;
#endif
}