#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseItem;
class Events;

enum ItemType
{
    ANTIDOTE = 0,
    PHOENIXDOWNI,
    PHOENIXDOWNII,
    PHOENIXDOWNIII,
    PHOENIXDOWNIV
};

class BaseBag
{
    int nItem;

public:
    BaseItem *head;
    BaseBag();
    ~BaseBag();
    int nItems() { return nItem; }
    void deleteItem(BaseItem*);
    void reduceItem(int);
    virtual void insertFirst(BaseItem *item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
};

enum Opponent
{
    madbear = 1,
    bandit,
    lordlupin,
    elf,
    troll,
    tornbery,
    queen_of_card,
    omega_weapon = 10,
    hades,
    UlTIMECIA = 99
};
class BaseOpponent
{
protected:
    int baseDam;
    int gil;
    int levelO;
    Opponent type;

public:
    int hp;
    int Damage(int level)
    {
        return baseDam * (levelO - level);
    }
    int BaseDame() { return baseDam; }
    int Gil() { return gil; }
    int LevelO() { return levelO; }
    Opponent Type() { return type; }
};

class MadBear : public BaseOpponent
{
public:
    MadBear(int i)
    {
        baseDam = 10;
        gil = 100;
        levelO = (i + 1) % 10 + 1;
        type = madbear;
    }
};

class BanDit : public BaseOpponent
{
public:
    BanDit(int i)
    {
        baseDam = 15;
        gil = 150;
        levelO = (i + 2) % 10 + 1;
        type = bandit;
    }
};

class LordLupin : public BaseOpponent
{
public:
    LordLupin(int i)
    {
        baseDam = 45;
        gil = 450;
        levelO = (i + 3) % 10 + 1;
        type = lordlupin;
    }
};

class Elf : public BaseOpponent
{
public:
    Elf(int i)
    {
        baseDam = 75;
        gil = 750;
        levelO = (i + 4) % 10 + 1;
        type = elf;
    }
};

class Troll : public BaseOpponent
{
public:
    Troll(int i)
    {
        baseDam = 95;
        gil = 800;
        levelO = (i + 5) % 10 + 1;
        type = troll;
    }
};

class Tornbery : public BaseOpponent
{
public:
    Tornbery(int i)
    {
        levelO = (i + 6) % 10 + 1;
        type = tornbery;
    }
};

class Queen_of_Card : public BaseOpponent
{
public:
    Queen_of_Card(int i)
    {
        levelO = (i + 7) % 10 + 1;
        type = queen_of_card;
    }
};

class Omega_Weapon : public BaseOpponent
{
public:
    Omega_Weapon(int i)
    {
        levelO = (i + 10) % 10 + 1;
        type = omega_weapon;
    }
};

class Hades : public BaseOpponent
{
public:
    Hades(int i)
    {
        levelO = (i + 11) % 10 + 1;
        type = hades;
    }
};

class Ultimecia : public BaseOpponent
{
public:
    Ultimecia()
    {
        hp = 5000;
        type = UlTIMECIA;
    }
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int nItemsMax;
    float baseDam;
    BaseBag *bag;  
    KnightType knightType;

public:
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    BaseKnight *next;
    string toString() const;
    bool isPaladin(int);
    bool isLancelot(int);
    bool isDragonKnight(int);

    int ID() { return id; }
    int MaxHP() { return maxhp; }
    int HP() { return hp; }
    int Gil() { return gil; }
    int Level() { return level; }
    int MaxItems() { return nItemsMax; }
    KnightType Type() { return knightType; }
    BaseBag *Bag() { return bag; }

    int damage () {return hp*level*baseDam;}
    void reduceHP (int a) {
        hp -= a;
    }
    void increaseHP (int a) {hp = a;}
    void addGil(int a);
    void addLevel(int i);
    void useItem();
    void addItems(BaseItem *);
    void loseItems(int);
    BaseKnight(int id, int maxhp, int level, int gil);
    ~BaseKnight();
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int id, int maxhp, int level, int gil)
        : BaseKnight(id, maxhp, level, gil)
    {
        knightType = PALADIN;
        baseDam = 0.06;
    }
};

class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int id, int maxhp, int level, int gil)
        : BaseKnight(id, maxhp, level, gil)
    {
        knightType = LANCELOT;
        baseDam = 0.05;
        nItemsMax = 16;
    }
};

class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int id, int maxhp, int level, int gil)
        : BaseKnight(id, maxhp, level, gil)
    {
        knightType = DRAGON;
        baseDam = 0.075;
        nItemsMax = 14;
    }
};

class NomalKnight : public BaseKnight
{
public:
    NomalKnight(int id, int maxhp, int level, int gil)
        : BaseKnight(id, maxhp, level, gil)
    {
        baseDam = 0;
        knightType = NORMAL;
        nItemsMax = 19;
    }
};

class ArmyKnights
{
private:
    BaseKnight *head;
    int nKnight;
    bool PaladinSheild, LancelotPear, GuineverseHair, ExcaliburSword;
    bool defeatOmega_Weapon, defeatHades;

public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    int count() const { return nKnight; }
    BaseKnight *lastKnight() const { return head; }

    bool hasPaladinShield() const { return PaladinSheild; }
    bool hasLancelotSpear() const { return LancelotPear; }
    bool hasGuinevereHair() const { return GuineverseHair; }
    bool hasExcaliburSword() const { return ExcaliburSword; }
    void KnightDeath(BaseKnight *);
    void Army_addGil(int);
    void Army_addItem(BaseItem *);
    void update();

    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem
{
protected:
    ItemType itemType;

public:
    BaseItem *next;
    BaseItem();
    ItemType Type() const { return itemType; }
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
};

class Anidote : public BaseItem
{
public:
    Anidote() : BaseItem() { itemType = ANTIDOTE; }
    bool canUse(BaseKnight *knight) { return true; }
    void use(BaseKnight *knight) { return; }
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI() : BaseItem() { itemType = PHOENIXDOWNI; }
    bool canUse ( BaseKnight * knight ) {
        if (knight -> HP() <= 0) return true;
    }
    void use ( BaseKnight * knight ) {
        knight -> increaseHP (knight -> MaxHP());
    }
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII() : BaseItem() { itemType = PHOENIXDOWNII; }
    bool canUse ( BaseKnight * knight ) {
        if (knight -> HP() < knight -> MaxHP() / 4) return true;
    }
    void use ( BaseKnight * knight ) {
        knight -> increaseHP (knight -> MaxHP());
    };
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII() : BaseItem() { itemType = PHOENIXDOWNIII; }
    bool canUse ( BaseKnight * knight ) {
        if (knight -> HP() < knight -> MaxHP() / 3) return true;
    }
    void use ( BaseKnight * knight ) {
        if (knight -> HP() < 0) knight -> increaseHP (knight -> MaxHP() / 3);
        else knight -> increaseHP (knight -> HP() + knight -> MaxHP() / 4);
    }
};

class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV() : BaseItem() { itemType = PHOENIXDOWNIV; }
    bool canUse ( BaseKnight * knight ) {
        if (knight -> HP() < knight -> MaxHP() / 2) return true;
    }
    void use ( BaseKnight * knight ) {
        if (knight -> HP() <= 0) knight -> increaseHP (knight -> MaxHP() / 2);
        else knight -> increaseHP (knight -> HP() + knight -> MaxHP() / 5);
    }
};

class Events
{
private:
    int nEvents, *events;

public:
    Events(const string &file_event);
    ~Events();
    int count() const { return nEvents; }
    int get(int i) const { return events[i]; }
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__