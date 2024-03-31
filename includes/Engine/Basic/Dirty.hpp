#include <vector>

class Dirty {
public:
    Dirty(const unsigned long size = 1);

    bool isDirty() const;

    bool isDirty(const unsigned int index) const;
    
    void clean();

    void clean(const unsigned int index);

protected:
    void makeDirty();
    
    void makeDirty(const unsigned int index);

private:
    unsigned long dirtyFlags;
};