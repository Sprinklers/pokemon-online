#ifndef MOVES_H
#define MOVES_H

#include <QtCore>
#include "battle.h"

/* MoveMechanics works by inserting functions into the contexts of the battle situation,
    that are then called when necessary. The functions are inserted by MoveEffect::setup,
    in fact it checks the non-NULL members of type 'function' of a derived class of MoveMechanics
    and insert them into the battle situation according to the name of the effect */
struct MoveMechanics
{
    MoveMechanics();
    /* Returns b.turnlong[player], used for convenience cuz shorter */
    static BattleSituation::context & turn(BattleSituation &b, int player);
    static BattleSituation::context & poke(BattleSituation &b, int player);

    typedef void (*function) (int source, int target, BattleSituation &b);

    QMap<QString, function> functions;
};

const int MOVE_MECHANICS_SIZE = 200;

/* Used to tell us everything about a move */
struct MoveEffect : public QVariantMap
{
    MoveEffect(int num);

    static void setup(int movenum, int source, int target, BattleSituation &b);

    static MoveMechanics *mechanics[MOVE_MECHANICS_SIZE];
    static QString names[MOVE_MECHANICS_SIZE];

    static void init();
};

/* For use with QVariants */
Q_DECLARE_METATYPE(QSharedPointer<QSet<QString> >)
Q_DECLARE_METATYPE(MoveMechanics::function)

#endif // MOVES_H