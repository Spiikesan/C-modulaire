# C-modulaire
Exemple d'implémentation de C modulaire en principe objet, avec quelques éléments de base


Ce répertoire contient mon travail sur le C modulaire :
* new/delete
* objets de base (vectors, lists, maps, buffers circulaires...)
* objets avancés (connexion tcp serveur/client, thread/mutexes)
* des utilitaires tels que le get_opt (gestion des paramètres passés au binaire), le splited (simple string split qui génère un tableau de char * selon un délimiteur fourni (espace par défaut))
* il y a aussi une gestion d'exception basée sur des macros et des objets (exception_handler, event_exception, exception)
* un très basique Event manager
* ansi qu'un garbage collector basique
* Et sûrement d'autres que j'oublie


Le tout est (normalement) compatible Linux/Windows


Le lambda n'est utilisable qu'avec GCC (fonctions imbriquées)


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
