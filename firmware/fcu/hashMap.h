# ifndef HashMap
# define HashMap

# define KeyType char *
# define ValueType void *

struct hashLink {
	KeyType key;
	ValueType value;
	struct hashLink * next;
};

struct hashMap {
	struct hashLink ** table;
	int tableSize;
	int count;
};

void initMap (struct hashMap * ht, int tableSize);
void insertMap (struct hashMap * ht, KeyType k, ValueType v);
ValueType atMap (struct hashMap * ht, KeyType k);
int containsKey (struct hashMap * ht, KeyType k);
void removeKey (struct hashMap * ht, KeyType k);
int size (struct hashMap * ht);

# endif
