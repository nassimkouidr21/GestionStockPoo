#include "CAD.h"

namespace Composant
{
    //le constructeur par d?faut
    CAD::CAD()
    {
        this->rq_sql = "RIEN"; //initialiser la requete ? RIEN
        //les informations de connexion ? la base de donn?es: le serveur; le nom de la BDD; le type de la s?curit?
        this->cnx = "Server=tcp:poo.database.windows.net,1433;Initial Catalog=Projetg1;Persist Security Info=False;User ID=nazim;Password=uLafdnE6-;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;";
        this->CNX = gcnew SqlConnection(this->cnx);//connexion ? la BDD SQL Server
        this->CMD = gcnew SqlCommand(this->rq_sql, this->CNX);//Initialise une nouvelle instance de la classe SqlCommand avec le texte de la requete et l'objet CNX
        this->CMD->CommandType = CommandType::Text;//d?finit le type de la commande ? texte
    }

    int CAD::actionRowsID(String^ rq_sql)
    {
        int id;
        this->setSQL(rq_sql);
        this->CMD->CommandText = this->rq_sql;
        this->CNX->Open();
        id = Convert::ToInt32(this->CMD->ExecuteScalar()); //r?cuperer la valeur de l'id lors de l'?x?cution de la requete
        this->CNX->Close();
        return id;
    }//permet de r?cup?rer l'ID courant

    void CAD::actionRows(String^ rq_sql)
    {
        this->setSQL(rq_sql);
        this->CMD->CommandText = this->rq_sql;
        this->CNX->Open();
        this->CMD->ExecuteNonQuery();//retourne le nbr de lignes affect?es par la commande (rq_sql)
        this->CNX->Close();
    }

    DataTable^ CAD::getRows(String^ rq_sql)
    {
        this->setSQL(rq_sql);
        this->DA = gcnew SqlDataAdapter(this->CMD);
        this->CMD->CommandText = this->rq_sql;
        this->DS = gcnew DataTable();
        this->DA->Fill(this->DS);//remplir le dataset avec la table sp?cifi?e en ex?cutant la requete de commande
        return this->DS;
    }
    
    void CAD::setSQL(String^ rq_sql)
    {
        if (rq_sql == "" || rq_sql == "RIEN")
        {
            this->rq_sql = "RIEN";
        }
        else
        {
            this->rq_sql = rq_sql;//SELECT/INSERT/UPDATE/CREATE
        }
    }

    //destructeur 
    CAD::~CAD(void)
    {
        delete this->cnx;
        delete this->rq_sql;
        delete this->CNX;
        delete this->DA;
        delete this->DS;
        delete this;
    }
}