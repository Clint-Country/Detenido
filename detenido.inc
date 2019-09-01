#if defined _detenido_included
	#endinput
#endif
#define _detenido_included


#if !defined _samp_included
       #error "Necesitas incluir a_samp"
	#include <a_samp>
#endif

#if !defined sscanf
	#tryinclude "../include/sscanf2"
#endif
#if !defined sscanf
	#tryinclude "../sscanf2"
#endif
#if !defined sscanf
    #error "Necesitas Incluir sscanf2"
	#include <sscanf2>
#endif


#if !defined CMD
    #tryinclude "../include/zcmd.inc"
#endif
#if !defined CMD
    #tryinclude "../zcmd.inc"
#endif
#if !defined CMD
    #tryinclude <zcmd>
#endif
#if !defined CMD
    #tryinclude "../include/Pawn.CMD.inc"
#endif
#if !defined CMD
    #tryinclude "../Pawn.CMD.inc"
#endif
#if !defined CMD
	#tryinclude <Pawn.CMD>
#endif
#if !defined CMD
    #error "Este requiere los siguientes inc ZCMD/Pawn.CMD para funcionar."
#endif

#if !defined ACTUALIZACION_IN
	#define  ACTUALIZACION_IN 1000 
#endif

#if !defined ESPOSADO_DISTANCIA
	#define ESPOSADO_DISTANCIA 3.0 //test
#endif

#if !defined DESESPOSADO_DISTANCIA
	#define DESESPOSADO_DISTANCIA 3.0 //test
#endif

#if !defined DISTANCIA_SEGUIRME
	#define DISTANCIA_SEGUIRME 4.0 //test
#endif

#if !defined RANGO_DE_CORRER
	#define RANGO_DE_CORRER 2.0 //test
#endif

#if !defined RANGO_TP
	#define RANGO_TP 15.0 //test
#endif

#if !defined COLOR_COMANDO_INFORMACION
	#define COLOR_COMANDO_INFORMACION "{D6E6FF}"
#endif

#if !defined COLOR_COMANDO_NOTA
	#define COLOR_COMANDO_NOTA "{e67e22}"
#endif

#if !defined COLOR_COMANDO_FALLIDO
	#define COLOR_COMANDO_FALLIDO "{c0392b}"
#endif

#if !defined COLOR_COMANDO_EXITOSO
	#define COLOR_COMANDO_EXITOSO "{2ecc71}"
#endif


enum
{
	VERIFICAR_ESTADO_DESESPOSADO, 
	VERIFICAR_ESTADO_ESPOSADO,
	VERIFICAR_ESTADO_SEGUIRME,
	VERIFICAR_ESTADO_ESPERA
};


enum resultados
{
    RESULTADO_ERROR_ID,
    RESULTADO_ERROR_P,
    RESULTADO_ERROR_U,
    RESULTADO_ERROR_ES,
    RESULTADO_ERROR_DE,
    RESULTADO_ERROR_SE,
    RESULTADO_ERROR_DI
};


static 
	detenid[MAX_PLAYERS] =
		{INVALID_PLAYER_ID, INVALID_PLAYER_ID, ...},

	Esposad_playerid[MAX_PLAYERS] =
		{INVALID_PLAYER_ID, INVALID_PLAYER_ID, ...},



static stock const vehiculos_asientos[212] =
{
	4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2,
	1, 4, 4, 4, 2, 1, 9, 1, 2, 2, 1, 2, 9, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 6,
	1, 2, 1, 1, 1, 2, 2, 2, 4, 4, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 4, 2, 1, 1, 2,
	2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2, 4, 2, 4, 1, 2, 2, 2, 4, 4, 2,
	2, 2, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1, 1, 2, 2, 2, 2,
	2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 0, 0, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
	4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1,
	2, 2, 2, 2, 4, 4, 2, 4, 1, 1, 4, 2, 2, 2, 2, 6, 1, 2, 2, 2, 1, 4, 4, 4, 2,
	2, 2, 2, 2, 4, 2, 1, 1, 1, 4, 1, 1
};

stock Float: Distancia_Jugadores(player_x, player_y)
{
	new 
		Float: x,
		Float: y,
		Float: z,
		Float: x2,
		Float: y2,
		Float: z2;

	GetPlayerPos(player_x, x, y, z);
	GetPlayerPos(player_y, x2, y2, z2);
	return VectorSize(x-x2, y-y2, z-z2);
}

stock JugadorEstadoEsposad(suspenid)
{
	return (Estado_suspendido{suspenid}) ? (1) : (0);
}


stock EstablecerS(suspenid, Float: look_x, Float: look_y)
{
	new 
		Float: x,
		Float: y,
		Float: a;

	GetPlayerPos(suspenid, x, y, a);
	a = atan2(look_y - y, look_x - x) - 90.0;
	SetPlayerFacingAngle(suspenid, a);
	return 1;
}

stock VerificarAsientos(vehicleid)
{
    new
        tmp,
        seat;

#if defined foreach  
    foreach(Player, i)
#else
    for(new i = 0; i < GetPlayerPoolSize(); i++)
#endif
    {
        if(GetPlayerVehicleID(i) == vehicleid)
        {
            if(0 <= (seat = GetPlayerVehicleSeat(i)) < cellbits)
            {
                tmp |= 1 << seat;
            }
        }
    }

    tmp = ~tmp;
    for(new i = 1; i < vehiculos_asientos[GetVehicleModel(vehicleid) - 400];
    	i++)
    {
    	if((~(tmp - 1) & tmp) == 1 << i)
    	{
    		return i;
    	}
    }
    return -1;
}
