#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// compatible to `string`
struct PodaString {
    char const *ptr;
    int32_t len;
};

// the code is edited based on generated output

struct PodaArray {
    struct Poda const *ptr;
    int32_t len;
};
struct PodaMap {
    struct PodaEntry const *ptr;
    int32_t len;
};

enum PodaType {
    PodaType_Null,
    PodaType_Bool,
    PodaType_Int,
    PodaType_Int64,
    PodaType_UInt64,
    PodaType_Float64,
    PodaType_String,
    PodaType_Array,
    PodaType_Map,
    PodaType_Foreign
};

struct Poda {
    enum PodaType type_;
    union {
        bool bool_;
        int32_t int_;
        int64_t int64_;
        uint64_t uint64_;
        double float64_;
        struct PodaString string_;
        struct PodaArray const *array_;
        struct PodaMap const *map_;
        void *foreign_;
    };
};

typedef enum PodaType PodaType;
typedef struct PodaArray PodaArray;
typedef struct PodaMap PodaMap;
typedef struct Poda Poda;
typedef struct PodaEntry PodaEntry;

struct Poda Poda_null(void);

struct Poda Poda_ofBool(bool value);

struct Poda Poda_ofInt(int32_t value);

struct Poda Poda_ofInt64(int64_t value);

struct Poda Poda_ofUInt64(uint64_t value);

struct Poda Poda_ofFloat64(double value);

struct Poda Poda_ofString(struct String value);

struct Poda Poda_unsafeOfCString(char const *value);

struct Poda Poda_emptyArray(void);

struct Poda Poda_unsafeWrapArray(struct PodaArray array);

struct Poda Poda_emptyMap(void);

struct Poda Poda_unsafeWrapMap(struct PodaMap map);

struct Poda Poda_createForeign(void *ptr);

struct PodaEntry PodaEntry_create(struct String key, struct Poda value);

struct String PodaEntry_key(struct PodaEntry e);

struct Poda PodaEntry_value(struct PodaEntry e);

bool Poda_isNull(struct Poda value);

bool Poda_asBool(struct Poda value, bool *writtenTo);

bool Poda_asInt(struct Poda value, int32_t *writtenTo);

bool Poda_asInt64(struct Poda value, int64_t *writtenTo);

bool Poda_asUInt64(struct Poda value, uint64_t *writtenTo);

bool Poda_asFloat64(struct Poda value, double *writtenTo);

bool Poda_asArray(struct Poda value, struct PodaArray *writtenTo);

bool Poda_asMap(struct Poda value, struct PodaMap *writtenTo);

bool Poda_asForeign(struct Poda value, void **writtenTo);
