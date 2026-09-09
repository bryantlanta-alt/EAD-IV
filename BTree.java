// Classe que representa um nó da Árvore B
class BTreeNode {
    int[] keys; // Array de chaves do nó
    int t;      // Grau mínimo (define o intervalo de chaves no nó)
    BTreeNode[] C; // Array de ponteiros para os filhos
    int n;      // Número atual de chaves no nó
    boolean leaf; // Verdadeiro se o nó for uma folha

    // Construtor
    public BTreeNode(int t, boolean leaf) {
        this.t = t;
        this.leaf = leaf;
        // O número máximo de chaves é 2*t - 1
        this.keys = new int[2 * t - 1];
        // O número máximo de filhos é 2*t
        this.C = new BTreeNode[2 * t];
        this.n = 0;
    }

    // Função para percorrer e imprimir a árvore
    public void traverse() {
        int i;
        for (i = 0; i < this.n; i++) {
            // Se não for folha, percorre o filho antes de imprimir a chave
            if (!this.leaf) {
                C[i].traverse();
            }
            System.out.print(keys[i] + " ");
        }
        // Percorre o último filho
        if (!leaf) {
            C[i].traverse();
        }
    }

    // Função para buscar uma chave na subárvore com raiz neste nó
    public BTreeNode search(int k) {
        int i = 0;
        // Encontra a primeira chave maior ou igual a k
        while (i < n && k > keys[i]) {
            i++;
        }
        // Se a chave encontrada for igual a k, retorna o nó
        if (i < n && keys[i] == k) {
            return this;
        }
        // Se a chave não for encontrada e for folha, a chave não existe
        if (leaf) {
            return null;
        }
        // Vai para o filho apropriado
        return C[i].search(k);
    }

    // Insere uma nova chave em um nó que NÃO está cheio
    public void insertNonFull(int k) {
        int i = n - 1;
        if (leaf) {
            // Encontra a posição da nova chave e move as chaves maiores para a direita
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }
            // Insere a nova chave
            keys[i + 1] = k;
            n++;
        } else {
            // Encontra o filho que vai receber a nova chave
            while (i >= 0 && keys[i] > k) {
                i--;
            }
            // Se o filho estiver cheio, divide o filho
            if (C[i + 1].n == 2 * t - 1) {
                splitChild(i + 1, C[i + 1]);
                if (keys[i + 1] < k) {
                    i++;
                }
            }
            C[i + 1].insertNonFull(k);
        }
    }

    // Divide o filho y deste nó. y deve estar cheio
    public void splitChild(int i, BTreeNode y) {
        // Cria um novo nó que vai guardar as (t-1) chaves de y
        BTreeNode z = new BTreeNode(y.t, y.leaf);
        z.n = t - 1;

        // Copia as últimas (t-1) chaves de y para z
        for (int j = 0; j < t - 1; j++) {
            z.keys[j] = y.keys[j + t];
        }

        // Copia os últimos t filhos de y para z
        if (!y.leaf) {
            for (int j = 0; j < t; j++) {
                z.C[j] = y.C[j + t];
            }
        }

        // Reduz o número de chaves em y
        y.n = t - 1;

        // Cria espaço neste nó para o novo filho
        for (int j = n; j >= i + 1; j--) {
            C[j + 1] = C[j];
        }
        C[i + 1] = z;

        // Encontra a posição para a nova chave neste nó e move as chaves
        for (int j = n - 1; j >= i; j--) {
            keys[j + 1] = keys[j];
        }
        // Sobe a chave do meio de y para este nó
        keys[i] = y.keys[t - 1];
        n++;
    }

    // --- MÉTODOS DE REMOÇÃO ---

    public void remove(int k) {
        int idx = findKey(k);

        // A chave k está presente neste nó
        if (idx < n && keys[idx] == k) {
            if (leaf) {
                removeFromLeaf(idx);
            } else {
                removeFromNonLeaf(idx);
            }
        } else {
            // A chave não está neste nó
            if (leaf) {
                System.out.println("A chave " + k + " não existe na árvore.");
                return;
            }

            // A chave pode estar na subárvore com raiz no filho idx
            boolean flag = (idx == n);

            // Se o filho onde a chave deve estar tem menos do que t chaves, preenche
            if (C[idx].n < t) {
                fill(idx);
            }

            // Se o último filho foi fundido (merged), ele diminuiu, chamamos o filho correto
            if (flag && idx > n) {
                C[idx - 1].remove(k);
            } else {
                C[idx].remove(k);
            }
        }
    }

    // Encontra a posição de uma chave
    private int findKey(int k) {
        int idx = 0;
        while (idx < n && keys[idx] < k) {
            idx++;
        }
        return idx;
    }

    private void removeFromLeaf(int idx) {
        // Desloca todas as chaves após idx uma posição para trás
        for (int i = idx + 1; i < n; ++i) {
            keys[i - 1] = keys[i];
        }
        n--;
    }

    private void removeFromNonLeaf(int idx) {
        int k = keys[idx];

        // Se o filho que precede k (C[idx]) tem pelo menos t chaves
        if (C[idx].n >= t) {
            int pred = getPred(idx);
            keys[idx] = pred;
            C[idx].remove(pred);
        }
        // Se o filho C[idx] tiver menos de t chaves, verifica o sucessor C[idx+1]
        else if (C[idx + 1].n >= t) {
            int succ = getSucc(idx);
            keys[idx] = succ;
            C[idx + 1].remove(succ);
        }
        // Se ambos C[idx] e C[idx+1] tiverem t-1 chaves, faz o merge
        else {
            merge(idx);
            C[idx].remove(k);
        }
    }

    // Pega o predecessor (maior chave da subárvore esquerda)
    private int getPred(int idx) {
        BTreeNode cur = C[idx];
        while (!cur.leaf) {
            cur = cur.C[cur.n];
        }
        return cur.keys[cur.n - 1];
    }

    // Pega o sucessor (menor chave da subárvore direita)
    private int getSucc(int idx) {
        BTreeNode cur = C[idx + 1];
        while (!cur.leaf) {
            cur = cur.C[0];
        }
        return cur.keys[0];
    }

    // Preenche o filho C[idx] que tem menos de t chaves
    private void fill(int idx) {
        // Tenta pegar emprestado do irmão anterior
        if (idx != 0 && C[idx - 1].n >= t) {
            borrowFromPrev(idx);
        }
        // Tenta pegar emprestado do próximo irmão
        else if (idx != n && C[idx + 1].n >= t) {
            borrowFromNext(idx);
        }
        // Se nenhum puder ceder chaves, faz o merge (fusão)
        else {
            if (idx != n) {
                merge(idx);
            } else {
                merge(idx - 1);
            }
        }
    }

    private void borrowFromPrev(int idx) {
        BTreeNode child = C[idx];
        BTreeNode sibling = C[idx - 1];

        // Move todas as chaves em child um passo para a frente
        for (int i = child.n - 1; i >= 0; --i) {
            child.keys[i + 1] = child.keys[i];
        }
        if (!child.leaf) {
            for (int i = child.n; i >= 0; --i) {
                child.C[i + 1] = child.C[i];
            }
        }
        // A primeira chave do filho recebe a chave do nó atual
        child.keys[0] = keys[idx - 1];
        if (!child.leaf) {
            child.C[0] = sibling.C[sibling.n];
        }
        // Move a última chave do irmão para o nó pai
        keys[idx - 1] = sibling.keys[sibling.n - 1];
        child.n += 1;
        sibling.n -= 1;
    }

    private void borrowFromNext(int idx) {
        BTreeNode child = C[idx];
        BTreeNode sibling = C[idx + 1];

        // A última chave do filho recebe a chave atual do pai
        child.keys[(child.n)] = keys[idx];
        if (!child.leaf) {
            child.C[(child.n) + 1] = sibling.C[0];
        }
        // A chave do pai recebe a primeira chave do irmão
        keys[idx] = sibling.keys[0];

        // Move todas as chaves do irmão um passo para trás
        for (int i = 1; i < sibling.n; ++i) {
            sibling.keys[i - 1] = sibling.keys[i];
        }
        if (!sibling.leaf) {
            for (int i = 1; i <= sibling.n; ++i) {
                sibling.C[i - 1] = sibling.C[i];
            }
        }
        child.n += 1;
        sibling.n -= 1;
    }

    private void merge(int idx) {
        BTreeNode child = C[idx];
        BTreeNode sibling = C[idx + 1];

        // Desce uma chave do nó atual para o filho
        child.keys[t - 1] = keys[idx];

        // Copia as chaves do irmão para o filho
        for (int i = 0; i < sibling.n; ++i) {
            child.keys[i + t] = sibling.keys[i];
        }
        if (!child.leaf) {
            for (int i = 0; i <= sibling.n; ++i) {
                child.C[i + t] = sibling.C[i];
            }
        }
        // Move as chaves do nó atual para cobrir o buraco da chave que desceu
        for (int i = idx + 1; i < n; ++i) {
            keys[i - 1] = keys[i];
        }
        for (int i = idx + 2; i <= n; ++i) {
            C[i - 1] = C[i];
        }
        child.n += sibling.n + 1;
        n--;
    }
}

// Classe Principal da Árvore B
public class BTree {
    BTreeNode root;
    int t; // Grau mínimo

    public BTree(int t) {
        this.root = null;
        this.t = t;
    }

    public void traverse() {
        if (this.root != null) {
            this.root.traverse();
        }
        System.out.println();
    }

    public BTreeNode search(int k) {
        return (root == null) ? null : root.search(k);
    }

    public void insert(int k) {
        if (root == null) {
            // Árvore vazia, aloca a raiz
            root = new BTreeNode(t, true);
            root.keys[0] = k;
            root.n = 1;
        } else {
            // Se a raiz estiver cheia, a altura da árvore cresce
            if (root.n == 2 * t - 1) {
                BTreeNode s = new BTreeNode(t, false);
                s.C[0] = root; // Antiga raiz se torna filha da nova raiz
                s.splitChild(0, root);

                // Decide qual dos dois filhos vai receber a nova chave
                int i = 0;
                if (s.keys[0] < k) {
                    i++;
                }
                s.C[i].insertNonFull(k);
                root = s; // Atualiza a raiz
            } else {
                // Se a raiz não estiver cheia, chama a inserção direta
                root.insertNonFull(k);
            }
        }
    }

    public void remove(int k) {
        if (root == null) {
            System.out.println("A árvore está vazia!");
            return;
        }
        root.remove(k);

        // Se após a remoção a raiz ficou sem chaves
        if (root.n == 0) {
            if (root.leaf) {
                root = null; // A árvore ficou vazia
            } else {
                root = root.C[0]; // O único filho se torna a nova raiz (altura diminui)
            }
        }
    }

    // Método principal para testar o código
    public static void main(String[] args) {
        BTree t = new BTree(3); // Árvore B de grau mínimo 3

        // Inserção
        int[] valoresParaInserir = {10, 20, 5, 6, 12, 30, 7, 17};
        for (int valor : valoresParaInserir) {
            t.insert(valor);
        }

        System.out.println("Árvore após inserção:");
        t.traverse();

        // Remoção
        System.out.println("\nRemovendo o 6");
        t.remove(6);
        t.traverse();

        System.out.println("\nRemovendo o 10 (Nó interno)");
        t.remove(10);
        t.traverse();
    }
}