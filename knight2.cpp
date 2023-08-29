#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */

// constructor
Events::Events (const string& file_event) {
    fstream f;
    f.open (file_event, ios :: in);
    f >> nEvents;
    events = new int [nEvents];
    for (int i = 0; i < nEvents; i++) f >> events[i];
    f.close();
}

BaseBag::BaseBag() {
    nItem = 0;
    head = NULL;
}

BaseItem::BaseItem () {
    next = NULL;
}

BaseKnight::BaseKnight (int id,int maxhp,int level,int gil){
    this -> id = id;
    this -> hp = maxhp;
    this -> maxhp = maxhp;
    this -> level = level;
    this -> gil = gil;
    bag = new BaseBag;
}

BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight* s;
    if (s -> isPaladin(maxhp)) s = new PaladinKnight (id, maxhp, level, gil);
    else if (s -> isLancelot(maxhp)) s = new LancelotKnight (id, maxhp, level, gil);
    else if (s -> isDragonKnight(maxhp)) s = new DragonKnight (id, maxhp, level, gil);
    else s = new NomalKnight (id, maxhp, level, gil);
    if (phoenixdownI > 0 || antidote > 0) {
        for (int i = 0; i < phoenixdownI; i++){
            PhoenixDownI* temp  = new PhoenixDownI;
            s -> bag -> insertFirst (temp);
        }
        for (int i = 0; i < antidote; i++){
            Anidote* temp = new Anidote;
            s -> bag -> insertFirst (temp);
        }
    }
    s -> next = NULL;
    return s;
}

ArmyKnights::ArmyKnights (const string &file_armyknights){
    fstream f(file_armyknights, ios::in);
    f >> nKnight;
    head = NULL;
    for (int i = 0; i < nKnight; i++){
        int maxhp, level, gil, antidote, phoenixdownI;
        f >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        BaseKnight* temp = BaseKnight::create(i + 1, maxhp, level, gil, antidote, phoenixdownI);
        if (head == NULL) head = temp;
        else {
            temp -> next = head;
            head = temp;
        }
    }
    f.close();
    defeatOmega_Weapon = false;
    defeatHades = false;
    PaladinSheild = false;
    LancelotPear = false;
    GuineverseHair = false;
    ExcaliburSword = false;
}


// destructor
Events::~Events () {
    delete [] events;
    nEvents = 0;
}

ArmyKnights::~ArmyKnights() {
    while (head != NULL) {
        BaseKnight* temp = head;
        head = head -> next;
        delete temp;
    }
}

BaseKnight::~BaseKnight() {
    next = NULL;
    delete bag;
}

BaseBag::~BaseBag() {
    nItem = 0;
    while (head != NULL) {
        BaseItem* temp = head;
        head = head -> next;
        delete temp;
    }
    head = NULL;
}




// BaseKnight
bool BaseKnight::isPaladin (int maxhp) {
    if (maxhp < 2) return false;
    if (maxhp == 2) return true;
    int k = sqrt (maxhp);
    for (int i = 2; i <= k; i++)
        if (maxhp % i == 0) return false;
    return true;
}

bool BaseKnight::isLancelot (int maxhp) {
    return maxhp == 888 ? true : false;
}

bool BaseKnight::isDragonKnight (int maxhp) {
    if (maxhp < 100) return false;
    int a = pow(maxhp / 100, 2), b = pow((maxhp % 100) / 10, 2), c = pow(maxhp % 10, 2);
    if (a == b + c) return true;
    if (b == a + c) return true;
    if (c == a + b) return true;
    return false;
}

void BaseKnight::addGil (int Gil) {
    gil += Gil;
    if (gil > 999) gil = 999;
    if (gil < 0) gil = 0;
}

void BaseKnight::addLevel (int i) {
    level += i;
    if (level > 10 ) level = 10;
    if (level < 0) level = 0;
}

void BaseKnight::addItems (BaseItem* item) {
    bag -> insertFirst (item);
}

void BaseKnight::useItem () {
    BaseItem* temp = bag -> head;
    while (this -> hp <= 0 && bag -> nItems() > 0 && temp != NULL) {
        if (temp -> canUse (this)) {
            temp -> use (this);
            BaseItem* ItemNext = temp -> next;
            bag -> deleteItem (temp);
            temp = ItemNext;
        }
    }
    if (this -> hp <= 0 && this -> gil >= 100) {
        this -> gil -= 100;
        this -> hp = this -> maxhp / 2;
    }
}

void BaseKnight::loseItems(int n) {
    BaseItem* p = bag -> get (ANTIDOTE);
    if (p == NULL)
        bag -> reduceItem(n);
    else {
        bag -> deleteItem (p);
    }
}

void BaseBag::reduceItem (int n) {
    if (nItem <= n) delete this;
    else {
        for (int i = 0; i < n; i ++) {
            BaseItem* temp = head;
            deleteItem (temp);
        }
    }
}

void BaseBag::insertFirst (BaseItem* temp) {
    nItem ++;
    if (head == NULL) {
        head = temp;
        head -> next = NULL;
    }
    else {
        temp -> next = head;
        head = temp;
    }
}

BaseItem* BaseBag::get(ItemType itemType) {
    BaseItem* p = head;
    while (p != NULL) {
        if (p -> Type() == itemType) return p;
        p = p -> next;
    }
    return NULL;
}

void BaseBag::deleteItem(BaseItem* temp) {
    if (temp == head) {
        head = head -> next;
        delete temp;
        nItem --;
    }
    else if (temp -> next == NULL) {
        delete temp;
        temp = NULL;
    }
    else {
        BaseItem* node;
        while (node -> next != temp) node = node -> next;
        node -> next = temp -> next;
        delete temp;
        nItem --;
    }
}

string BaseBag::toString() const {
    string s = "";
    s += "Bag[count=" + to_string(nItem) + ";";
    if (head == NULL) {
        s.pop_back();
        s += "]";
        return s;
    }

        if (head -> Type() == 0) s += "Antidote";
        else if (head -> Type() == 1) s += "PhoenixI";
        else if (head -> Type() == 2) s += "PhoenixII";
        else if (head -> Type() == 3) s += "PhoenixIII";
        else if (head -> Type() == 4) s += "PhoenixIV";
        s += ",";

    s.pop_back();
    s += "]";
    return s;


}

bool ArmyKnights::fight(BaseOpponent* opponent) {
    if (opponent -> Type() >= 1 && opponent -> Type() <= 5) {

            if (head -> Type() == LANCELOT || head -> Type() == PALADIN) return true;
            if (head -> Level() < opponent -> LevelO()) return false;
            return true;
    }
    else if (opponent -> Type() == 10) {
            if (head -> Level() == 10 && head -> HP() == head -> MaxHP()) return true;
            if (head -> Type() == DRAGON) return true;
            return false;
    }
    else if (opponent -> Type() == 11) {
            if (head -> Level() == 10) return true;
            if (head -> Type() == PALADIN && head -> Level() >= 8) return true;
            return false;
    }
    else if (opponent -> Type() == 99) {
            BaseKnight* temp = head;
            if (hasExcaliburSword()) return true;
            if (!hasGuinevereHair() || !hasLancelotSpear() || !hasPaladinShield()) return false;
            while (temp != NULL) {
                if (temp -> Type() == NORMAL) {
                    temp = temp -> next;
                    continue;
                }
                opponent -> hp -= temp -> damage();
                if (opponent -> hp <= 0) return true;
                BaseKnight* death = temp;
                temp = temp -> next;
                KnightDeath(death);
            }
            return false;
    }
}

bool ArmyKnights::adventure (Events* events) {
    for (int i = 0; i < events -> count(); i++ ) {
        if (events -> get(i) == 1) {
            MadBear bear(i);
            if (fight (&bear))
                Army_addGil (bear.Gil());
            else {
                head -> reduceHP (bear.Damage(head -> Level()));
                update();
            }
        }
        else if (events -> get(i) == 2) {
            BanDit ban(i);
            if (fight (&ban))
                Army_addGil (ban.Gil());
            else {
                head -> reduceHP (ban.Damage(head -> Level()));
                update();
            }
        }
        else if (events -> get(i) == 3) {
            LordLupin lord(i);
            if (fight (&lord))
                Army_addGil (lord.Gil());
            else {
                head -> reduceHP (lord.Damage(head -> Level()));
                update();
            }
        }
        else if (events -> get(i) == 4) {
            Elf el(i);
            if (fight (&el))
                Army_addGil (el.Gil());
            else {
                head -> reduceHP (el.Damage(head -> Level()));
                update();
            }
        }
        else if (events -> get(i) == 5) {
            Troll tro(i);
            if (fight (&tro))
                Army_addGil (tro.Gil());
            else if (!(head -> Type() == DRAGON)) {
                head -> reduceHP (tro.Damage(head -> Level()));
                update();
            }
        }
        else if (events -> get(i) == 6) {
            Tornbery tor(i);
            if (fight (&tor))
                head -> addLevel(1);
            else if (!(head -> Type() == DRAGON))
                head -> loseItems (3);
        }
        else if (events -> get(i) == 7) {
            Queen_of_Card queen(i);
            if (fight (&queen))
                Army_addGil(head -> Gil());
            else if (!(head -> Type() == PALADIN))
                Army_addGil(- head -> Gil() / 2);
        }
        else if (events -> get(i) == 8) {
            if (head -> Type() == PALADIN) {
                if (head -> HP() < head -> MaxHP() / 3) {
                    head -> increaseHP (head -> HP() + head -> MaxHP() / 5);
                }
            }
            else if (head -> Gil() >= 50) {
                if (head -> HP() < head -> MaxHP() / 3) {
                    head -> addGil (-50);
                    head -> increaseHP (head -> HP() + head -> MaxHP() / 5);
                }
            }
        }
        else if (events -> get(i) == 9) head -> increaseHP (head -> MaxHP());
        else if (events -> get(i) == 10 && !defeatOmega_Weapon) {
            Omega_Weapon ow(i);
            if (fight(&ow)) {
                defeatOmega_Weapon = true;
                head -> addLevel(10 - head -> Level());
                head -> addGil(999 - head -> Gil());
            }
            else {
                head -> reduceHP (head -> HP());
                update();
            }
        }
        else if (events -> get(i) == 11 && !defeatHades) {
            Hades hd(i);
            if (fight(&hd)) {
                if (!hasPaladinShield()) {
                    PaladinSheild = true;
                }
                defeatHades = true;
            }
            else {
                head -> reduceHP (head -> HP());
                update();
            }
        }
        else if (events -> get(i) == 99) {
            Ultimecia ulti;
            if (!fight (&ulti)) {
                while (head != NULL) {
                BaseKnight* temp = head;
                head = head -> next;
                delete [] temp;
                }
                nKnight = 0;
            }
        }
        else if (events -> get(i) == 112) {
            PhoenixDownII* phoenix;
            Army_addItem (phoenix);
        }
        else if (events -> get(i) == 113) {
            PhoenixDownIII* phoenix;
            Army_addItem (phoenix);
        }
        else if (events -> get(i) == 114) {
            PhoenixDownIV* phoenix;
            Army_addItem (phoenix);
        }
        else if (events -> get(i) == 95 && hasPaladinShield() == false) {
            PaladinSheild = true;
        }
        else if (events -> get(i) == 96 && hasLancelotSpear() == false) {
            LancelotPear = true;
        }
        else if (events -> get(i) == 97 && hasGuinevereHair() == false) {
            GuineverseHair = true;
        }
        else if (events -> get(i) == 98 && hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()){
            ExcaliburSword = true;
        }
        printInfo();
        if (nKnight <= 0) return false;
    }
    if (nKnight > 0) return true;
}

void ArmyKnights::KnightDeath(BaseKnight* temp) {
    if (temp == head) {
        head = head -> next;
        delete temp;
    }
    else if (temp -> next == NULL) {
        delete temp;
        temp = NULL;
    }
    else {
        BaseKnight* node;
        while (node -> next != temp) node = node -> next;
        node -> next = temp -> next;
        delete temp;
    }
    nKnight --;
}

void ArmyKnights::Army_addGil (int gil) {
    BaseKnight* temp = head;
    while (temp != NULL && gil > 0) {
        if (temp -> Gil() + gil > 999) {
            gil = 999 - temp -> Gil();
            temp -> addGil (999 - gil);
        }
        else {
            temp -> addGil (gil);
            gil = 0;
        }
        temp = temp -> next;
    }
    if (gil < 0) temp -> addGil(gil);
}

void ArmyKnights::Army_addItem (BaseItem* item) {
    BaseKnight* temp = head;
    while (temp != NULL) {
        if (temp -> Bag() -> nItems() < temp -> MaxItems() || temp -> Type() == PALADIN){
            temp -> addItems(item);
            return;
        }
        temp = temp -> next;
    }
}


void ArmyKnights::update() {
    head -> useItem();
    if (head -> HP() < 0) {
        KnightDeath (head);
    }
}


void KnightAdventure::loadArmyKnights(const string &s){armyKnights = new ArmyKnights(s);}

void KnightAdventure::loadEvents (const string &s) { events = new Events(s); }

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}

void KnightAdventure::run () {
    bool res = armyKnights -> adventure (events);
    armyKnights -> printResult (res);
}
