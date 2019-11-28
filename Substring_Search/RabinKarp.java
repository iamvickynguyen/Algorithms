
/******************************************************************************
 * Author: Vicky Nguyen 
 * Reference: https://algs4.cs.princeton.edu/53substring

 *  Compilation:  javac RabinKarp.java
 *  Execution:    java RabinKarp pat txt
 *  Dependencies: System.out.java
 *
 *  Reads in two strings, the pattern (containing 1 wildcard, i.e. '*') and the input text, and
 *  searches for the pattern in the input text using the
 *  Las Vegas version of the Rabin-Karp algorithm.
 *
 *  % java RabinKarp abracadabr* abacadabrabracabracadabrabrabracad
 *  pattern: abracadabra
 *  text:    abacadabrabracabracadabrabrabracad 
 *  match:                 abrac*dabra          
 ******************************************************************************/

import java.math.BigInteger;
import java.util.Random;

public class RabinKarp {
    private String pat; // the pattern // needed only for Las Vegas
    private long patHash; // pattern hash value
    private int m; // pattern length
    private long q; // a large prime, small enough to avoid long overflow
    private int R; // radix
    private long RM; // R^(M-1) % Q
    private long RM_pattern; // R^(M-star-1) % Q
    private int star; // wildcard index
    private long const_value; // hash value of pattern without '*' character

    /**
     * Preprocesses the pattern string.
     *
     * @param pattern the pattern string
     * @param R       the alphabet size
     */
    public RabinKarp(char[] pattern, int R) {
        this.pat = String.valueOf(pattern);
        this.R = R;
        throw new UnsupportedOperationException("Operation not supported yet");
    }

    /**
     * Preprocesses the pattern string.
     *
     * @param pat the pattern string
     */
    public RabinKarp(String pat) {
        this.pat = pat; // save pattern (needed only for Las Vegas)
        R = 256;
        m = pat.length();
        q = longRandomPrime();
        this.star = findStar(pat);

        // precompute R^(m-1) % q for use in removing leading digit
        RM = 1;
        for (int i = 1; i <= m - 1; i++)
            RM = (R * RM) % q;

        // precompute R^(m-star-1) % q for use in removing star digit
        RM_pattern = 1;
        for (int j = 1; j <= m - 1 - star; j++)
            RM_pattern = (R * RM_pattern) % q;

        const_value = hash(pat, m);
    }

    // find star position
    private int findStar(String text) {
        for (int i = 0; i < text.length(); i++) {
            if (text.charAt(i) == '*')
                return i;
        }
        // no wildcard
        System.err.println("Error: no wildcard");
        System.exit(0);
        return -1;
    }

    // Compute hash for key[0..m-1].
    private long hash(String key, int m) {
        long h = 0;
        for (int j = 0; j < m; j++) {
            if (key.charAt(j) == '*') {
                h = (R * h) % q; // add 0
            } else {
                h = (R * h + key.charAt(j)) % q;
            }
        }

        return h;
    }

    // Las Vegas version: does pat[] match txt[i..i-m+1] ?
    private boolean check(String txt, int i) {
        for (int j = 0; j < m; j++)
            if (pat.charAt(j) != txt.charAt(i + j))
                return false;
        return true;
    }

    // Monte Carlo version: always return true
    // private boolean check(int i) {
    // return true;
    // }

    /**
     * Returns the index of the first occurrrence of the pattern string in the text
     * string.
     *
     * @param txt the text string
     * @return the index of the first occurrence of the pattern string in the text
     *         string; n if no such match
     */
    public int search(String txt, String pattern) {
        int n = txt.length();
        if (n < m)
            return n;
        long txtHash = hash(txt, m);

        // hash first pattern
        pat = changeString(pattern, star, txt.charAt(star));
        patHash = hash(pat, m);

        // check for match at offset 0
        if ((patHash == txtHash) && check(txt, 0))
            return 0;

        // check for hash match; if hash match, check for exact match
        for (int i = m, j = star; i < n; i++, j++) {
            // Remove leading digit, add trailing digit, check for match.
            txtHash = (txtHash + q - RM * txt.charAt(i - m) % q) % q;
            txtHash = (txtHash * R + txt.charAt(i)) % q;

            // rolling hash for pattern
            patHash = (const_value - txt.charAt(j) * RM_pattern % q) % q;
            patHash = (const_value + txt.charAt(j + 1) * RM_pattern % q) % q;

            // update pattern
            pat = changeString(pat, star, txt.charAt(j + 1));

            // match
            int offset = i - m + 1;
            if ((patHash == txtHash) && check(txt, offset))
                return offset;
        }

        // no match
        return n;
    }

    // replace a char in string
    public String changeString(String s, int index, char key) {
        char[] tmp = s.toCharArray();
        tmp[index] = key;
        String st = String.valueOf(tmp);
        return st;
    }

    // a random 31-bit prime
    private static long longRandomPrime() {
        BigInteger prime = BigInteger.probablePrime(31, new Random());
        return prime.longValue();
    }

    /**
     * Takes a pattern string and an input string as command-line arguments;
     * searches for the pattern string in the text string; and prints the first
     * occurrence of the pattern string in the text string.
     *
     * @param args the command-line arguments
     */
    public static void main(String[] args) {
        String pat = args[0];
        String txt = args[1];

        RabinKarp searcher = new RabinKarp(pat);
        int offset = searcher.search(txt, pat);

        // print results
        System.out.println("text:    " + txt);

        // from brute force search method 1
        System.out.print("pattern: ");
        for (int i = 0; i < offset; i++)
            System.out.print(" ");
        System.out.println(pat);
    }
}