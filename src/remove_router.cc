#include "create_model.h"
#include "utils.h"


/** given router sequence:
 *       A -> B -> C
 * we can remove B, iff:
 *     1) A and C are on the same plane
 *     2) no other references to B exist.
 */
void Model::remove_router()
{
}
