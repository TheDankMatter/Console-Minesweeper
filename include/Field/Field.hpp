class Field {
    private:
        bool hidden;
        unsigned short int number;
        bool flag;
        bool bomb;
    public:
        Field();
        bool isHidden();
        unsigned short int getNumber();
        bool isFlag();
        bool isBomb();
        void revealField();
        void setNumber(unsigned short int number);
        void addOne();
        void placeBomb();
        void placeFlag();
        void removeFlag();
};                             