#ifndef PLAYER_H
#define PLAYER_H

#include "../PokemonInfo/networkstructs.h"
#include "analyze.h"

/* a single player */
class Player : public QObject
{
    Q_OBJECT
public:
    enum State
    {
	NotLoggedIn,
	LoggedIn,
	Challenged,
	Battling
    };
    enum ChallengeDesc
    {
	Sent,
	Accepted,
	Canceled,
	Busy,
	Refused
    };

    Player(QTcpSocket *sock);
    ~Player();

    /* returns all the regular info */
    TeamInfo &team();
    const TeamInfo &team() const;
    /* Converts the content of the TeamInfo to a basicInfo and returns it */
    BasicInfo basicInfo() const;

    /* Sends a message to the player */
    void sendMessage(const QString &mess);

    void setId(int id);
    int id() const;
    QString name() const;

    bool connected() const;
    bool isLoggedIn() const;
    bool battling() const;
    void changeState(int newstate);
    int state() const;

    int opponent () const;
    bool isChallenged() const;
    int challengedBy() const;
    bool hasChallenged(int id) const;


    /* Sends the challenge, returns false if can't even send the challenge */
    bool challenge(int id);

    void startBattle(int id, const TeamBattle &team);
    void battleResult(int result);

    void sendChallengeStuff(int stuff, int otherparty);
    void addChallenge(int id);
    void cancelChallenges();

    Analyzer& relay();
    const Analyzer& relay() const;
signals:
    void loggedIn(int id, const QString &name);
    void recvMessage(int id, const QString &mess);
    void disconnected(int id);
    void recvTeam(int id);

    void challengeStuff(int desc, int idfrom, int idto);
    void battleFinished(int desc, int winner, int loser);

    void battleMessage(int id,const BattleChoice &b);

public slots:
    void loggedIn(const TeamInfo &team);
    void recvMessage(const QString &mess);
    void recvTeam(const TeamInfo &team);
    void disconnected();
    void challengeStuff(int desc, int id);
    void battleForfeited();
    void battleMessage(const BattleChoice &b);
private:
    TeamInfo myteam;
    Analyzer myrelay;
    int myid;

    QSet<int> m_challenged;
    int m_challengedby;
    int m_opponent;
    int m_state;

    void removeChallenge(int id);
};

#endif // PLAYER_H