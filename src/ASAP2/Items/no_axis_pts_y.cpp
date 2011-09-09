#include "no_axis_pts_y.h"
#include <QMessageBox>
#include "a2lgrammar.h"

//initialise static variables
Factory<Item,NO_AXIS_PTS_Y> NO_AXIS_PTS_Y::itemFactory;

NO_AXIS_PTS_Y::NO_AXIS_PTS_Y(Node *parentNode)  : Item(parentNode)
{
    //get grammar
    A2lGrammar* gram = parentNode->lex->grammar;
    namePar = &gram->no_axis_pts_y.namePar;
    typePar = &gram->no_axis_pts_y.typePar;

    //Parse Mandatory PARAMETERS
    parseFixPar(typePar);
    name = (char*)"NO_AXIS_PTS_Y";
}

NO_AXIS_PTS_Y::~NO_AXIS_PTS_Y()
{
    foreach (char* ptr, parameters)
    {
        delete[] ptr;
    }
}

void NO_AXIS_PTS_Y::parseFixPar(QList<TokenTyp> *typePar)
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

QMap<std::string, std::string> NO_AXIS_PTS_Y::getParameters()
{
    QMap<std::string, std::string> par;
    for (int i = 0; i < namePar->count(); i++)
    {
        par.insert(namePar->at(i), parameters.at(i));
    }
    return par;
}

char* NO_AXIS_PTS_Y::getPar(std::string str)
{
    int i = namePar->indexOf(str);
    return parameters.at(i);
}