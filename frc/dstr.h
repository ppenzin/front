/** \file dstr.h
 *
 * Dynamic string type
 */

typedef struct dstr_ dstr_t;

/** Create a new dynamic string and initialize to empty
 *
 * \return dynamic string pointer or NULL if allocation fails, should be freed
 *         only using free_dstr()
 */
dstr_t * new_dstr(void);

/** Free a dynamic string entity
 *
 * \param dstr pointer to the object to free
 */
void free_dstr(dstr_t * dstr);

/** Set string's value
 *
 * \param to dstr entity to modify, unchanged on memory allocation failure
 * \param from C-string value to set
 * \return pointer to updated entity, NULL if memory allocation failed
 */
dstr_t * dstr_cpy(dstr_t * to, const char * from);

/** Append a single character (as produced by getc)
 *
 * \param to entity to update, unchanged on memory allocation failure
 * \param c character to write
 * \return pointer to updated entity, NULL if memory allocation failed
 */
dstr_t * dstr_addc(dstr_t * to, int c);

/** Append a null-terminated string
 *
 * \param to entity to update, unchanged on memory allocation failure
 * \param s string to append
 * \return pointer to updated entity, NULL if memory allocation failed
 */
dstr_t * dstr_adds(dstr_t * to, const char * s);

/** Return string contents as cstr
 *
 * \param d dstr to read from
 * \return pointer to null-terminated string with d's contents
 *
 * The contents of returned string are owned by the object it came from
 */
const char * dstr_cstr(dstr_t * d);
