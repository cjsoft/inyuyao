import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

public class Tests {
    int MAX_Q = 140000;
    int MAX_N = 52000;
    int flag = 0;

    Random rnd = new Random(239);

    public static void main(String[] args) throws FileNotFoundException {
        new Tests().gen();
    }

    int tests = 1;

    private void shuffleEdges(int[] dx, int[] dy) {
        int n = dx.length;
        for (int i = 0; i < n; i++) {
            int t = rnd.nextInt(2);
            if (t == 1) {
                int tmp = dx[i];
                dx[i] = dy[i];
                dy[i] = tmp;
            }
        }
        for (int i = 0; i < n; i++) {
            int j = rnd.nextInt(i + 1);
            
            int tmp = dx[i];
            dx[i] = dx[j];
            dx[j] = tmp;
            
            tmp = dy[i];
            dy[i] = dy[j];
            dy[j] = tmp;
        }
    }

    private void shiftVertices(int n, int[] dx, int[] dy, int q, int[] qx, int[] qy) {
        int start = rnd.nextInt(n);
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = (start + i) % n;
        }
        if (rnd.nextInt(2) == 1) {
            for (int i = 0; i < n - i - 1; i++) {
                int tmp = v[i];
                v[i] = v[n - i - 1];
                v[n - i - 1] = tmp;
            }
        }
        for (int i = 0; i < n - 3; i++) {
            dx[i] = v[dx[i]];
            dy[i] = v[dy[i]];
        }
        for (int i = 0; i < q; i++) {
            qx[i] = v[qx[i]];
            qy[i] = v[qy[i]];
        }
    }
    
    public void writeTestAsIs(int n, int[] dx, int[] dy, int q, int[] qx, int[] qy) {
        try {
            PrintWriter out = new PrintWriter(String.format("drive%d.in", tests++));
            System.err.println("Writing test " + (tests - 1));
            out.println(n);
            for (int i = 0; i < n - 3; i++) {
                out.println(dx[i] + " " + dy[i]);
            }
            out.println(q);
            for (int i = 0; i < q; i++) {
                out.println(qx[i] + " " + qy[i]);
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public void writeTest(int n, int[] dx, int[] dy, int q, int[] qx, int[] qy) {
        try {
            PrintWriter out = new PrintWriter(String.format("drive%d.in", tests++));

            System.err.println("Writing test " + (tests - 1));

            shiftVertices(n, dx, dy, q, qx, qy);

            shuffleEdges(dx, dy);
            shuffleEdges(qx, qy);

            out.println(n);

            for (int i = 0; i < n - 3; i++) {
                out.println((dx[i] + 1) + " " + (dy[i] + 1));
            }

            out.println(q);
            
            for (int i = 0; i < q; i++) {
                out.println((qx[i] + 1) + " " + (qy[i] + 1));
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public void writeTestWithRandomQueries(int n, int[] dx, int[] dy, int q) {
        int[] qx = new int[q];
        int[] qy = new int[q];
        for (int i = 0; i < q; i++) {
            qx[i] = rnd.nextInt(n);
            qy[i] = rnd.nextInt(n);
        }
        writeTest(n, dx, dy, q, qx, qy);
    }

    private int cur_id;

    private void drawRandomEdges(int[] v, int[] dx, int[] dy) {
        int sz = v.length;
        if (sz <= 3) {
            return;
        }
        int x, y;
        int diff;
        do {
            x = rnd.nextInt(sz);
            y = rnd.nextInt(sz);
            diff = Math.abs(x - y);
            diff = Math.min(diff, sz - diff);
        } while (x >= y || diff <= 1);
        dx[cur_id] = v[x];
        dy[cur_id] = v[y];
        cur_id++;
        int[] va = new int[y - x + 1];
        int[] vb = new int[sz + 2 - (y - x + 1)];
        int ia = 0;
        for (int i = x; i <= y; i++) {
            va[ia++] = v[i];
        }
        int ib = 0;
        for (int i = 0; i <= x; i++) {
            vb[ib++] = v[i];
        }
        for (int i = y; i < sz; i++) {
            vb[ib++] = v[i];
        }
        drawRandomEdges(va, dx, dy);
        drawRandomEdges(vb, dx, dy);
    }

    public void genRandom(int n, int q) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        cur_id = 0;
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        drawRandomEdges(v, dx, dy);
        writeTestWithRandomQueries(n, dx, dy, q);
    }

    public void genRandomWithAllQueries(int n) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        cur_id = 0;
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        drawRandomEdges(v, dx, dy);
        int q = (int) Math.min(n * 1L * n, 2L * n);
        int[] qx = new int[q];
        int[] qy = new int[q];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i * n + j < q) {
                    qx[i * n + j] = i;
                    qy[i * n + j] = j;
                } else {
                  break;
                }
            }
            if (i * n > q) {
              break;
            }
        }
        writeTest(n, dx, dy, q, qx, qy);
    }

    public void genAllFromOne(int n, int q) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        for (int i = 0; i < n - 3; i++) {
            dx[i] = 0;
            dy[i] = i + 2;
        }
        writeTestWithRandomQueries(n, dx, dy, q);
    }

    public void genSequence(int n, int q, int a, int b) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        int x = 0, y = 2;
        for (int i = 0; i < n - 3; i++) {
            dx[i] = x;
            dy[i] = y;
            if (rnd.nextInt(a + b) < a) {
               y = (y + 1) % n;
            } else {
               x = (x + n - 1) % n;
            }
        }
        writeTestWithRandomQueries(n, dx, dy, q);
    }

    public void genSequenceExchange(int n, int q) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        int x = 0, y = 2;
        for (int i = 0; i < n - 3; i++) {
            dx[i] = x;
            dy[i] = y;
            if (i % 2 == 0) {
               y = (y + 1) % n;
            } else {
               x = (x + n - 1) % n;
            }
        }
        writeTestWithRandomQueries(n, dx, dy, q);
    }
    public void drawSequenceExchange(int[] v, int[] dx, int[] dy) {
        int n = v.length;
        int x = 0, y = 2;
        for (int i = 0; i < n - 3; i++) {
            dx[cur_id] = v[x];
            dy[cur_id] = v[y];
            ++cur_id;
            if (i % 2 == 0) {
               y = (y + 1) % n;
            } else {
               x = (x + n - 1) % n;
            }
        }
    }

    private void drawBisection(int[] v, int[] dx, int[] dy) {
        int sz = v.length;
        if (sz <= 3) {
            return;
        }
        int x = rnd.nextInt(2 * sz / 5);
        int y = x + 3 * sz / 5;
        dx[cur_id] = v[x];
        dy[cur_id] = v[y];
        cur_id++;
        int[] va = new int[y - x + 1];
        int[] vb = new int[sz + 2 - (y - x + 1)];
        int ia = 0;
        for (int i = x; i <= y; i++) {
            va[ia++] = v[i];
        }
        int ib = 0;
        for (int i = 0; i <= x; i++) {
            vb[ib++] = v[i];
        }
        for (int i = y; i < sz; i++) {
            vb[ib++] = v[i];
        }
        drawTrisection(vb, dx, dy);
        drawSequenceExchange(va, dx, dy);
    }

    public void genBisection(int n, int q) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        cur_id = 0;
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        drawBisection(v, dx, dy);
        writeTestWithRandomQueries(n, dx, dy, q);
    }

    private void drawTrisection(int[] v, int[] dx, int[] dy) {
        int sz = v.length;
        if (sz <= 5) {
            drawRandomEdges(v, dx, dy);
            return;
        } 
        int x = rnd.nextInt(sz / 3);
        int y = x + sz / 3;
        int z = x + 2 * sz / 3;
        dx[cur_id] = v[x];
        dy[cur_id] = v[y];
        cur_id++;
        dx[cur_id] = v[x];
        dy[cur_id] = v[z];
        cur_id++;
        dx[cur_id] = v[y];
        dy[cur_id] = v[z];
        cur_id++;
        int[] va = new int[y - x + 1];
        int[] vb = new int[z - y + 1];
        int[] vc = new int[sz + 2 - (z - x + 1)];
        int ia = 0;
        for (int i = x; i <= y; i++) {
            va[ia++] = v[i];
        }
        int ib = 0;
        for (int i = y; i <= z; i++) {
            vb[ib++] = v[i];
        }
        int ic = 0;
        for (int i = 0; i <= x; i++) {
            vc[ic++] = v[i];
        }
        for (int i = z; i < sz; i++) {
            vc[ic++] = v[i];
        }
        drawTrisection(va, dx, dy);
        drawTrisection(vb, dx, dy);
        drawTrisection(vc, dx, dy);
    }

    public void genTrisection(int n, int q) {
        int[] dx = new int[n - 3];
        int[] dy = new int[n - 3];
        cur_id = 0;
        int[] v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        drawTrisection(v, dx, dy);
        writeTestWithRandomQueries(n, dx, dy, q);
    }

    public void gen() {
        for (int n = 1; n <= 20; n++) {
            flag = 0;
            double x = Math.pow((Math.log(n) / Math.log(1.22)), 4);
            int m = Math.max(10, (int)x);
            genBisection(m, 2 * m);
        }
    }
}
