# C-modulaire
Exemple d'implémentation de C modulaire en principe objet, avec quelques éléments basiques. Les macros sont beaucoup utilisées pour le méta-langage

Ce répertoire contient quelques éléments de mon travail sur le C modulaire :


* new/delete avec arguments par défaut
* Introspection native lors de la conception des objets => [Voir l'exemple correspondant](/examples/introspection)
* Booléens immuables avec opérations booléennes simplifiées
* Collections:
  * Itérables (avec la macro FOREACH): vector, list, map(avec pair), buffer circulaires
  * Non itérable: linked_list, splitted, varargs
* objets avancés (connexion tcp serveur/client, thread, mutexes)
* des utilitaires:
  * get_opt (gestion des options passés au binaire) => [exemple](/examples/binary_options)
  * splitted (découpage de chaine selon séparateurs)
  * fonctions "lambda"
* il y a aussi une gestion d'exception basée sur des macros et des objets (exception_handler, event_exception, exception) => [exemple](/examples/exception_handling)
* un Event manager (observable) => [exemple 1 (en singleton)](/examples/event-singleton_event_manager), [exemple 2 (collection observable)](/examples/event2-observable_collection)
* un garbage collector simple (utilisant atexit)

Je rajouterai d'autres éléments quand l'envie m'en prendra. Je suis également ouvert à tout commentaire ou toute proposition concernant ce projet

Le tout est compatible Linux/Windows avec GCC


## Disclaimer:

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
