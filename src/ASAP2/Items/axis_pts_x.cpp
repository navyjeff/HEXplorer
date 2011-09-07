#include "axis_pts_x.h"
#include <QMessageBox>
#include "a2lgrammar.h"

//initialise static variables
Factory<Item,AXIS_PTS_X> AXIS_PTS_X::itemFactory;

AXIS_PTS_X::AXIS_PTS_X( Node *parentNode)  : Item(parentNode)
{
    //get grammar
    A2lGrammar* gram = parentNode->lex->grammar;
    namePar = &gram->axis_pts_x.namePar;
    typePar = &gram->axis_pts_x.typePar;

    //Parse Mandatory PARAMETERS
    parseFixPar(typePar );
    name = (char*)"AXIS_PTS_X";
}

AXIS_PTS_X::~AXIS_PTS_X()
{
    foreach (char* ptr, parameters)
    {
        delete[] ptr;
    }
}

void AXIS_PTS_X::parseFixPar(QList<TokenTyp> *typePar)
{
    //Mandatory PARAMETERS
    TokenTyp token;
    for (int i = 0; i < typePar->count(); i++)
    {
        token = this->nextToken();
        if (token == typePar->at(i))
        {
            char *c = new char[parentNode->lex->getLexem().length()+1];
            strcpy(c, parentNode->lex->getLexem().c_str());
            parameters.append(c);
        }
        else
        {
            QString t(this->parentNode->lex->toString(typePar->at(i)).c_str());
            QString s(this->parentNode->lex->toString(token).c_str());
            this->showError("expected token : " + t +"\nfind token : " + s);
        }
    }
}

QMap<std::string, std::string> AXIS_PTS_X::getParameters()
{
    QMap<std::string, std::string> par;
    for (int i = 0; i < namePar->count(); i++)
    {
        par.insert(namePar->at(i), parameters.at(i));
    }
    return par;
}

char* AXIS_PTS_X::getPar(std::string str)
{
    int i = namePar->indexOf(str);
    return parameters.at(i);
}
