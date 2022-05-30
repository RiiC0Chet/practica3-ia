# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const
{
    /*
    switch(id)
    {
        case 0:
            thinkAleatorio(c_piece,id_piece,dice);
        break;

        case 1:
            thinkAleatorioMasInteligente(c_piece,id_piece,dice);
        break;
            
        case 2:
            thinkFichaMasAdelantada(c_piece,id_piece,dice);
        break;

        case 3:
            thinkMejorOpcion(c_piece,id_piece,dice);
        break;
    }
    */
        
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    //valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    int profundidad = 0;
    switch(id)
    {
        case 0:    
            valor = Poda_AlfaBeta(*actual, jugador, profundidad, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, profundidad, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, Heuristica_UNO);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 2:
            valor = Poda_AlfaBeta(*actual, jugador, profundidad, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, Heuristica_DOS);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 3:
            valor = Poda_AlfaBeta(*actual, jugador, profundidad, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, Heuristica_TRES);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 4:
            valor = Poda_AlfaBeta(*actual, jugador, profundidad, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, Heuristica_CUATRO);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
    }
    //cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    
}


void AIPlayer::thinkAleatorio(color & c_piece, int & id_piece, int & dice) const
{
        // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if(current_pieces.size() > 0){
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else{
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }

}


void AIPlayer::thinkAleatorioMasInteligente(color & c_piece,int & id_piece,int & dice)const
{
    // El color de ficha que se vaamover.
    c_piece = actual->getCurrentColor();
    // Vector que almacenará los dados que se pueden usar para el movimiento.
    vector<int>current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int>current_pieces;
    // Se obtiene el vector de dados que se pueden usar para el movimiento.
    current_dices = actual->getAvailableDices(c_piece);
    // En vez de elegir un dado al azar,miro primero cuáles tienen fichas que se puedan mover.
    vector<int>current_dices_que_pueden_mover_ficha;

    for(int i=0;i<current_dices.size();i++)
    {
        // Se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces=actual->getAvailablePieces(c_piece,current_dices[i]);
        // Si se pueden mover fichas para el dado actual,lo añado al vector de dados que pueden mover fichas.
        if(current_pieces.size()>0)
        {
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }
    }

    // Si no tengo ninun dado que pueda mover fichas,paso turno con un dado al azar(la macro SKIP TURN me permite no mover).
    if(current_dices_que_pueden_mover_ficha.size()==0)
    {
        dice=current_dices[rand() % current_dices.size()];
        id_piece=SKIP_TURN;
    }
    // En caso contrario,elijo un dado de forma aleatoria de entre los que pueden mover ficha.
    else
    {
        dice=current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];
        // Se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces=actual->getAvailablePieces(c_piece,dice);
        // Muevo una ficha al azar de entre las que se pueden mover.
        id_piece = current_pieces[rand() % current_pieces.size()];
    }

}



void AIPlayer::thinkFichaMasAdelantada(color & c_piece,int & id_piece,int&dice)const
{
   // Elijo el dado haciendo lo mismo que el jugador anterior.
    thinkAleatorioMasInteligente(c_piece,id_piece,dice);
   // Tras llamaraesta función,ya tengo en dice el número de dado que quiero usar.
   // Ahora,en vez de mover una ficha al azar,voyamover la que esté más adelantada
    //(equivalentemente,la más cercanaala meta).
    vector<int>current_pieces = actual->getAvailablePieces(c_piece,dice);

    int id_ficha_mas_adelantada=-1;
    int min_distancia_meta=9999;

    for(int i=0;i<current_pieces.size();i++)
    {
       // distanceToGoal(color,id)devuelve la distanciaala meta de la ficha[id]del color que le indique.
        int distancia_meta=actual->distanceToGoal(c_piece,current_pieces[i]);

        if(distancia_meta<min_distancia_meta)
        {
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = current_pieces[i];
        }
    }
    // Si no he encontrado ninguna ficha,paso turno.
    if(id_ficha_mas_adelantada == -1)
    {
        id_piece=SKIP_TURN;
    }
   // En caso contrario,moveré la ficha más adelantada.
    else
    {
        id_piece=id_ficha_mas_adelantada;
    }
}


void AIPlayer::thinkMejorOpcion(color & c_piece,int & id_piece,int&dice)const
{
    color last_c_piece = none;
    int last_id_piece = -1; 
    int last_dice = -1;

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece,last_id_piece,last_dice);

    bool me_quedo_con_esta_accion = false;

    while(!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion)
    {
        if(siguiente_hijo.isEatingMove() || siguiente_hijo.isGoalMove() || (siguiente_hijo.gameOver() && siguiente_hijo.getWinner() == this->jugador))
            me_quedo_con_esta_accion = true;
        else
            siguiente_hijo = actual->generateNextMove(last_c_piece,last_id_piece,last_dice);
    }

    if(me_quedo_con_esta_accion)
    {
        c_piece = last_c_piece; 
        id_piece = last_id_piece;
        dice = last_dice;
    }
    else
        thinkAleatorioMasInteligente(c_piece,id_piece,dice);

}

// En esta primera heuristica distinguimos para cada jugador cual de los dos colores va con ventaja
// para poder aproevecharlo, se contabilizaran como puntos estar en el goal, en la recta final y no 
// se puntuara extra si hay fichas en casa (de la misma forma se puntua al oponente)
double AIPlayer::Heuristica_UNO(const Parchis &estado, int jugador)
{

//-----------------------------------------------------------------------------------------------------------------------------------------------
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {

//-----------------------------------------------------------------------------------------------------------------------------------------------
        // Puntuaciones asignadas a cada jugador en este estado del juego
        int puntuacion_jugador = 0;
        int puntuacion_oponente = 0;

//----------------------------------------Aqui vamos a asignar que color va ganando por cada jugador---------------------------------------------

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> my_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0 (que sera el total de casillas que les queda por recorrer para ganar)
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(0),0));
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(1),0));

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> op_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(0),0));
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(1),0));

        // colores auxiliares para poder medir que color va ganando para cada jugador
        color color_ganador_jugador,
                color_perdedor_jugador,
              color_ganador_oponente,
                color_perdedor_oponente;

        // Calculamos cual de los dos colores de cada  jugador y oponente va ganando 
        // Para ello vamos a calcular los puntos de cada color por jugador

        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i].first;
            color c_op = op_colors[i].first;

            for (int j = 0; j < num_pieces; j++)
            {
                my_colors[i].second += estado.distanceToGoal(c,j);
                op_colors[i].second += estado.distanceToGoal(c_op,j);
            }

                
        }

        // si se cumple es porque el colo 0 es va mejor en la partida que el 1
        if( my_colors[0].second <  my_colors[1].second)
        {// Para jugador
            color_ganador_jugador = my_colors[0].first;
            color_perdedor_jugador = my_colors[1].first; 
        }
        else
        {
            color_ganador_jugador = my_colors[1].first;
            color_perdedor_jugador = my_colors[0].first; 
        }
            
        if( op_colors[0].second <  op_colors[1].second)
        {// Para oponente
            color_ganador_oponente = op_colors[0].first;
            color_perdedor_oponente = op_colors[1].first; 
        }
        else
        {
            color_ganador_oponente = op_colors[1].first;
            color_perdedor_oponente = op_colors[0].first; 
        }
//-----------------------------------------------Contabilizamos los puntos para el color del jugador color ganador----------------------------------------------------------

    
        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_jugador, p).type == goal)
                puntuacion_jugador+=12;
            else if(estado.getBoard().getPiece(color_ganador_jugador, p).type == final_queue)
                puntuacion_jugador+=8;
            else if (estado.getBoard().getPiece(color_ganador_jugador, p).type != home)
                puntuacion_jugador+=5;
        }

        if(estado.eatenPiece().first == color_ganador_oponente)
            puntuacion_jugador+=9;
        
        if(estado.eatenPiece().first == color_perdedor_oponente)
            puntuacion_jugador+=6;

//-----------------------------------------------Contabilizamos los puntos para el color del jugador color perdedor----------------------------------------------------------

//-----------------------------------------------Contabilizamos los puntos para el color del oponente color ganador----------------------------------------------------------

        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_oponente, p).type == goal)
                puntuacion_oponente+=12;
            else if(estado.getBoard().getPiece(color_ganador_oponente, p).type == final_queue)
                puntuacion_oponente+=8;
            else if (estado.getBoard().getPiece(color_ganador_oponente, p).type != home)
                puntuacion_oponente+=5;
        }

        if(estado.eatenPiece().first == color_ganador_jugador)
            puntuacion_oponente+=9;
        
        if(estado.eatenPiece().first == color_perdedor_jugador)
            puntuacion_oponente+=6;
//-----------------------------------------------Contabilizamos los puntos para el color del oponente color perdedor----------------------------------------------------------
        
        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

// Con esta nueva heurisitica ademas de comprobar lo de la primera 
// estamos teniendo en cuenta la distancia al final cada vez mas chica lo cual se premia
double AIPlayer::Heuristica_DOS(const Parchis &estado, int jugador)
{

//-----------------------------------------------------------------------------------------------------------------------------------------------
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {

//-----------------------------------------------------------------------------------------------------------------------------------------------
        // Puntuaciones asignadas a cada jugador en este estado del juego
        double puntuacion_jugador = 0;
        double puntuacion_oponente = 0;

//----------------------------------------Aqui vamos a asignar que color va ganando por cada jugador---------------------------------------------

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> my_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0 (que sera el total de casillas que les queda por recorrer para ganar)
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(0),0));
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(1),0));

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> op_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(0),0));
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(1),0));

        // colores auxiliares para poder medir que color va ganando para cada jugador
        color color_ganador_jugador,
                color_perdedor_jugador,
              color_ganador_oponente,
                color_perdedor_oponente;

        // Calculamos cual de los dos colores de cada  jugador y oponente va ganando 
        // Para ello vamos a calcular los puntos de cada color por jugador

        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i].first;
            color c_op = op_colors[i].first;

            for (int j = 0; j < num_pieces; j++)
            {
                my_colors[i].second += estado.distanceToGoal(c,j);
                op_colors[i].second += estado.distanceToGoal(c_op,j);
            }

                
        }

        // si se cumple es porque el colo 0 es va mejor en la partida que el 1
        if( my_colors[0].second <  my_colors[1].second)
        {// Para jugador
            color_ganador_jugador = my_colors[0].first;
            color_perdedor_jugador = my_colors[1].first; 
        }
        else
        {
            color_ganador_jugador = my_colors[1].first;
            color_perdedor_jugador = my_colors[0].first; 
        }
            
        if( op_colors[0].second <  op_colors[1].second)
        {// Para oponente
            color_ganador_oponente = op_colors[0].first;
            color_perdedor_oponente = op_colors[1].first; 
        }
        else
        {
            color_ganador_oponente = op_colors[1].first;
            color_perdedor_oponente = op_colors[0].first; 
        }
//-----------------------------------------------Contabilizamos los puntos para el color del jugador color ganador----------------------------------------------------------

    
        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_jugador, p).type == goal)
                puntuacion_jugador+=12;
            else if(estado.getBoard().getPiece(color_ganador_jugador, p).type == final_queue)
                puntuacion_jugador+=8;
            else if (estado.getBoard().getPiece(color_ganador_jugador, p).type != home)
                puntuacion_jugador+=5;
            
            puntuacion_jugador+= (71-estado.distanceToGoal(color_ganador_jugador, p)) /5;
        }

        if(estado.eatenPiece().first == color_ganador_oponente)
            puntuacion_jugador+=11;
        
        if(estado.eatenPiece().first == color_perdedor_oponente)
            puntuacion_jugador+=6;

//-----------------------------------------------Contabilizamos los puntos para el color del jugador color perdedor----------------------------------------------------------

//-----------------------------------------------Contabilizamos los puntos para el color del oponente color ganador----------------------------------------------------------

        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_oponente, p).type == goal)
                puntuacion_oponente+=12;
            else if(estado.getBoard().getPiece(color_ganador_oponente, p).type == final_queue)
                puntuacion_oponente+=8;
            else if (estado.getBoard().getPiece(color_ganador_oponente, p).type != home)
                puntuacion_oponente+=5;

            puntuacion_oponente+= (71-estado.distanceToGoal(color_ganador_oponente, p)) /5;
        }

        if(estado.eatenPiece().first == color_ganador_jugador)
            puntuacion_oponente+=11;
        
        if(estado.eatenPiece().first == color_perdedor_jugador)
            puntuacion_oponente+=6;
//-----------------------------------------------Contabilizamos los puntos para el color del oponente color perdedor----------------------------------------------------------
       
        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


// Con esta nueva heurisitica ademas de comprobar lo de la segunda 
// estamos teniendo en cuenta si somos amenazados por otras fichas 
// o si amenazamos a otras fichas del color contrario
double AIPlayer::Heuristica_TRES(const Parchis &estado, int jugador)
{

//-----------------------------------------------------------------------------------------------------------------------------------------------
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {

//-----------------------------------------------------------------------------------------------------------------------------------------------
        // Puntuaciones asignadas a cada jugador en este estado del juego
        double puntuacion_jugador = 0;
        double puntuacion_oponente = 0;

//----------------------------------------Aqui vamos a asignar que color va ganando por cada jugador---------------------------------------------

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> my_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0 (que sera el total de casillas que les queda por recorrer para ganar)
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(0),0));
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(1),0));

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> op_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(0),0));
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(1),0));

        // colores auxiliares para poder medir que color va ganando para cada jugador
        color color_ganador_jugador,
                color_perdedor_jugador,
              color_ganador_oponente,
                color_perdedor_oponente;

        // Calculamos cual de los dos colores de cada  jugador y oponente va ganando 
        // Para ello vamos a calcular los puntos de cada color por jugador

        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i].first;
            color c_op = op_colors[i].first;

            for (int j = 0; j < num_pieces; j++)
            {
                my_colors[i].second += estado.distanceToGoal(c,j);
                op_colors[i].second += estado.distanceToGoal(c_op,j);
            }

                
        }

        // si se cumple es porque el colo 0 es va mejor en la partida que el 1
        if( my_colors[0].second <  my_colors[1].second)
        {// Para jugador
            color_ganador_jugador = my_colors[0].first;
            color_perdedor_jugador = my_colors[1].first; 
        }
        else
        {
            color_ganador_jugador = my_colors[1].first;
            color_perdedor_jugador = my_colors[0].first; 
        }
            
        if( op_colors[0].second <  op_colors[1].second)
        {// Para oponente
            color_ganador_oponente = op_colors[0].first;
            color_perdedor_oponente = op_colors[1].first; 
        }
        else
        {
            color_ganador_oponente = op_colors[1].first;
            color_perdedor_oponente = op_colors[0].first; 
        }
//-----------------------------------------------Contabilizamos los puntos para el color del jugador color ganador----------------------------------------------------------

    
        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_jugador, p).type == goal)
                puntuacion_jugador+=12;
            else if(estado.getBoard().getPiece(color_ganador_jugador, p).type == final_queue)
                puntuacion_jugador+=8;
            else if (estado.getBoard().getPiece(color_ganador_jugador, p).type != home)
                puntuacion_jugador+=7;
            
            puntuacion_jugador+= (71-estado.distanceToGoal(color_ganador_jugador, p)) /5;
        }

        // comprobamos si amenazamos a alguna ficha enemiga
        for (int fichas_mias = 0; fichas_mias < num_pieces; fichas_mias++)
        {
            // Recorro las fichas de ese color.
            for (int fichas_oponentes = 0; fichas_oponentes < num_pieces; fichas_oponentes++)
            {
                // comprobamos si fichas de nuetro ganador amenazan a su ganador
                if(estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) <= 6)
                    puntuacion_jugador+=0.5;

                // comprobamos si fichas de nuetro ganador amenazan a su perdedor
                if(estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) <= 6)
                    puntuacion_jugador+=0.15;
                
                // comprobamos si fichas de nuetro perdedor amenazan a su ganador
                if(estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) <= 6)
                    puntuacion_jugador+=0.5;

                // comprobamos si fichas de nuetro perdedor amenazan a su perdedor
                if(estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) <= 6)
                    puntuacion_jugador+=0.05;
            }
        }
            


        if(estado.eatenPiece().first == color_ganador_oponente)
            puntuacion_jugador+=11;
        
        if(estado.eatenPiece().first == color_perdedor_oponente)
            puntuacion_jugador+=6;

//-----------------------------------------------Contabilizamos los puntos para el color del jugador color perdedor----------------------------------------------------------

//-----------------------------------------------Contabilizamos los puntos para el color del oponente color ganador----------------------------------------------------------

        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_oponente, p).type == goal)
                puntuacion_oponente+=12;
            else if(estado.getBoard().getPiece(color_ganador_oponente, p).type == final_queue)
                puntuacion_oponente+=8;
            else if (estado.getBoard().getPiece(color_ganador_oponente, p).type != home)
                puntuacion_oponente+=7;

            puntuacion_oponente+= (71-estado.distanceToGoal(color_ganador_oponente, p)) /5;
        }

        // comprobamos si amenazamos a alguna ficha enemiga
        for (int fichas_mias = 0; fichas_mias < num_pieces; fichas_mias++)
        {
            // Recorro las fichas de ese color.
            for (int fichas_oponentes = 0; fichas_oponentes < num_pieces; fichas_oponentes++)
            {
                // comprobamos si fichas su ganador amenaza a mi ganador
                if(estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) <= 6)
                    puntuacion_oponente+=0.5;

                // comprobamos si fichas de su perdedor amenaza a mi ganador
                if(estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) <= 6)
                    puntuacion_oponente+=0.5;
                
                // comprobamos si fichas de su ganador amenaza a mi perdedor
                if(estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) <= 6)
                    puntuacion_oponente+=0.15;

                // comprobamos si fichas de su perdedor asmenaza a mi perdedor
                if(estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) <= 6)
                    puntuacion_oponente+=0.05;
            }
        }



        if(estado.eatenPiece().first == color_ganador_jugador)
            puntuacion_oponente+=11;
        
        if(estado.eatenPiece().first == color_perdedor_jugador)
            puntuacion_oponente+=6;
//-----------------------------------------------Contabilizamos los puntos para el color del oponente color perdedor----------------------------------------------------------
       
        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


// Con esta nueva heurisitica ademas de comprobar lo de la tercera
// pero ahora tenemos en cuenta que a la hora de amenazar o que nos amenacen 
// no estemos en casillas safe y si estamos en casillas safe a secas
double AIPlayer::Heuristica_CUATRO(const Parchis &estado, int jugador)
{

//-----------------------------------------------------------------------------------------------------------------------------------------------
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {

//-----------------------------------------------------------------------------------------------------------------------------------------------
        // Puntuaciones asignadas a cada jugador en este estado del juego
        double puntuacion_jugador = 0;
        double puntuacion_oponente = 0;

//----------------------------------------Aqui vamos a asignar que color va ganando por cada jugador---------------------------------------------

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> my_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0 (que sera el total de casillas que les queda por recorrer para ganar)
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(0),0));
            my_colors.push_back(make_pair(estado.getPlayerColors(jugador).at(1),0));

        // Colores que juega mi jugador y colores del oponente
        vector<pair<color,int>> op_colors; 
            // añadimos los colores del jugador, con el valor inicial que es 0
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(0),0));
            op_colors.push_back(make_pair(estado.getPlayerColors(oponente).at(1),0));

        // colores auxiliares para poder medir que color va ganando para cada jugador
        color color_ganador_jugador,
                color_perdedor_jugador,
              color_ganador_oponente,
                color_perdedor_oponente;

        // Calculamos cual de los dos colores de cada  jugador y oponente va ganando 
        // Para ello vamos a calcular los puntos de cada color por jugador

        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i].first;
            color c_op = op_colors[i].first;

            for (int j = 0; j < num_pieces; j++)
            {
                my_colors[i].second += estado.distanceToGoal(c,j);
                op_colors[i].second += estado.distanceToGoal(c_op,j);
            }

                
        }

        // si se cumple es porque el colo 0 es va mejor en la partida que el 1
        if( my_colors[0].second <  my_colors[1].second)
        {// Para jugador
            color_ganador_jugador = my_colors[0].first;
            color_perdedor_jugador = my_colors[1].first; 
        }
        else
        {
            color_ganador_jugador = my_colors[1].first;
            color_perdedor_jugador = my_colors[0].first; 
        }
            
        if( op_colors[0].second <  op_colors[1].second)
        {// Para oponente
            color_ganador_oponente = op_colors[0].first;
            color_perdedor_oponente = op_colors[1].first; 
        }
        else
        {
            color_ganador_oponente = op_colors[1].first;
            color_perdedor_oponente = op_colors[0].first; 
        }
//-----------------------------------------------Contabilizamos los puntos para el color del jugador color ganador----------------------------------------------------------

    
        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_jugador, p).type == goal)
                puntuacion_jugador+=18;
            else if(estado.getBoard().getPiece(color_ganador_jugador, p).type == final_queue)
                puntuacion_jugador+=8;
            else if (estado.getBoard().getPiece(color_ganador_jugador, p).type != home)
                puntuacion_jugador+=3;
            if(estado.isSafePiece(color_ganador_jugador,p))
                puntuacion_jugador+=2;

            puntuacion_jugador+= (71-estado.distanceToGoal(color_ganador_jugador, p)) /3;
        }

        // comprobamos si amenazamos a alguna ficha enemiga
        for (int fichas_mias = 0; fichas_mias < num_pieces; fichas_mias++)
        {
            // Recorro las fichas de ese color.
            for (int fichas_oponentes = 0; fichas_oponentes < num_pieces; fichas_oponentes++)
            {
                // comprobamos si fichas de nuetro ganador amenazan a su ganador
                if(estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) <= 6 && !estado.isSafePiece(color_ganador_oponente, fichas_oponentes))
                    puntuacion_jugador++;

                // comprobamos si fichas de nuetro ganador amenazan a su perdedor
                if(estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_ganador_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) <= 6 && !estado.isSafePiece(color_perdedor_oponente, fichas_oponentes))
                    puntuacion_jugador+=0.15;
                
                // comprobamos si fichas de nuetro perdedor amenazan a su ganador
                if(estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_ganador_oponente, fichas_oponentes) <= 6 && !estado.isSafePiece(color_ganador_oponente, fichas_oponentes))
                    puntuacion_jugador++;

                // comprobamos si fichas de nuetro perdedor amenazan a su perdedor
                if(estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) != -1 && estado.distanceBoxtoBox(color_perdedor_jugador,fichas_mias, color_perdedor_oponente, fichas_oponentes) <= 6 && !estado.isSafePiece(color_perdedor_oponente, fichas_oponentes))
                    puntuacion_jugador+=0.05;
            }
        }
            


        if(estado.eatenPiece().first == color_ganador_oponente)
            puntuacion_jugador+=16;
        
        if(estado.eatenPiece().first == color_perdedor_oponente)
            puntuacion_jugador+=6;

//-----------------------------------------------Contabilizamos los puntos para el color del jugador color perdedor----------------------------------------------------------

//-----------------------------------------------Contabilizamos los puntos para el color del oponente color ganador----------------------------------------------------------

        for(int p = 0;p<num_pieces;p++)
        {
            if(estado.getBoard().getPiece(color_ganador_oponente, p).type == goal)
                puntuacion_oponente+=18;
            else if(estado.getBoard().getPiece(color_ganador_oponente, p).type == final_queue)
                puntuacion_oponente+=8;
            else if (estado.getBoard().getPiece(color_ganador_oponente, p).type != home)
                puntuacion_oponente+=3;
            
            if(estado.isSafePiece(color_ganador_oponente,p))
                puntuacion_oponente+=2;

            puntuacion_oponente+= (71-estado.distanceToGoal(color_ganador_oponente, p)) /3;
        }

        // comprobamos si amenazamos a alguna ficha enemiga
        for (int fichas_mias = 0; fichas_mias < num_pieces; fichas_mias++)
        {
            // Recorro las fichas de ese color.
            for (int fichas_oponentes = 0; fichas_oponentes < num_pieces; fichas_oponentes++)
            {
                // comprobamos si fichas su ganador amenaza a mi ganador
                if(estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) <= 6 && !estado.isSafePiece(color_ganador_jugador,fichas_mias))
                    puntuacion_oponente++;

                // comprobamos si fichas de su perdedor amenaza a mi ganador
                if(estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_ganador_jugador,fichas_mias) <= 6 && !estado.isSafePiece(color_ganador_jugador,fichas_mias))
                    puntuacion_oponente++;
                
                // comprobamos si fichas de su ganador amenaza a mi perdedor
                if(estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_ganador_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) <= 6 && !estado.isSafePiece(color_perdedor_jugador,fichas_mias))
                    puntuacion_oponente+=0.15;

                // comprobamos si fichas de su perdedor asmenaza a mi perdedor
                if(estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) != -1 && estado.distanceBoxtoBox(color_perdedor_oponente, fichas_oponentes,color_perdedor_jugador,fichas_mias) <= 6 && !estado.isSafePiece(color_perdedor_jugador,fichas_mias))
                    puntuacion_oponente+=0.05;
            }
        }



        if(estado.eatenPiece().first == color_ganador_jugador)
            puntuacion_oponente+=16;
        
        if(estado.eatenPiece().first == color_perdedor_jugador)
            puntuacion_oponente+=6;
//-----------------------------------------------Contabilizamos los puntos para el color del oponente color perdedor----------------------------------------------------------
       
        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}






double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::Poda_AlfaBeta(const Parchis & hijo, int jugador, int  profundidad, const int PROFUNDIDAD,
                                color & c_piece, int & id_piece, int &dice, double alpha, double beta, 
                                double (*ptr_func)(const Parchis &, int)) const
{
    if(hijo.gameOver() || profundidad == PROFUNDIDAD)
        return ptr_func(hijo,jugador); // La victoria y la derrota se han dividido, volver a la valoración
    
		 

    color last_c_piece = none;
    int last_id_piece = -1; 
    int last_dice = -1;
    
    Parchis siguiente_hijo = hijo.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice);
	 if (actual->getCurrentPlayerId() != hijo.getCurrentPlayerId()) // juzga el tipo de nodo 
	 {// nodo mínimo
        //cout<<"Entramos en nodo minimo de profundidad :"<< profundidad<<endl;
		while(!(siguiente_hijo == hijo))
		{
          //  cout<<"Para el hijo generado  tenemos un color :"<<last_c_piece<<" id de pieza"<<last_id_piece<<" dado "<<last_dice<<endl;
		    double valor = Poda_AlfaBeta (siguiente_hijo,jugador,profundidad+1,PROFUNDIDAD,last_c_piece,last_id_piece,last_dice,alpha,beta,ptr_func); // Búsqueda recursiva de nodos secundarios

            //cout<<"****************************************************************************************** "<<alpha<<" "<<beta<<" "<<valor<<endl;

            if(valor<beta)
			{
				beta = valor; // El valor mínimo

                //beta = min(valor,beta);

                if(profundidad == 0)
                {
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                }
                
			}
                if(alpha>=beta)
					break;// Poda alfa, descarte el nodo sucesor 

            siguiente_hijo = hijo.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice);
			
		}
		 return beta; // Devuelve el valor mínimo 
	}
	else
	 {// El nodo con el valor máximo 
        //cout<<"Entramos en nodo maximo de profundidad :"<< profundidad<<endl;
		while(!(siguiente_hijo == hijo))
		{
			 //siguiente_hijo = hijo.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice); // Genera un nuevo nodo
			double valor = Poda_AlfaBeta (siguiente_hijo,jugador,profundidad+1,PROFUNDIDAD,last_c_piece,last_id_piece,last_dice,alpha,beta,ptr_func); // Búsqueda recursiva de nodos secundarios
			//cout<<"****************************************************************************************** "<<alpha<<" "<<beta<<" "<<valor<<endl;
            if(valor>alpha)
			{
				 alpha = valor; // El valor mínimo
                 
                if(profundidad == 0)
                {
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                }
			} 
            if(alpha>=beta)
					 break;// poda nBeta, descarta el nodo sucesor 
            siguiente_hijo = hijo.generateNextMoveDescending(last_c_piece,last_id_piece,last_dice);

		}
		 return alpha; // Devuelve el valor mínimo 
	} 
}