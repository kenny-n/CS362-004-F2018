// Kenny Ngo
// CS362 Fall 2018
// Final Project

import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorTest extends TestCase {

    public UrlValidatorTest(String testName) {
        super(testName);
    }

    private void testHelper(UrlValidator urlValidator, String url, String expected) {
        try {
            System.out.println("Testing URL='" + url + "'......");
            System.out.println("\tExpected: " + expected + "\t\tActual: " + urlValidator.isValid(url));
        } catch (Error e) {
            System.out.println("Error... " + e);
        } catch (Exception e) {
            System.out.println("Exception... " + e);
        }
    }

    public void testManualTest() {
        manualTest("default", urlValidatorOptions[0]);
        manualTest("UrlValidator.ALLOW_ALL_SCHEMES", urlValidatorOptions[1]);
        manualTest("UrlValidator.ALLOW_2_SLASHES", urlValidatorOptions[2]);
        manualTest("UrlValidator.NO_FRAGMENTS", urlValidatorOptions[3]);
        manualTest("UrlValidator.ALLOW_LOCAL_URLS", urlValidatorOptions[4]);
    }

    private void manualTest(String optionsName, long options) {
        System.out.println("Starting manual test with options=" + optionsName + "...");
        UrlValidator urlValidator = new UrlValidator(options);

        testHelper(urlValidator, "www.google.com", "true");
        testHelper(urlValidator, "http://www.google.com", "true");
        testHelper(urlValidator, "https://www.google.com", "true");
        testHelper(urlValidator, "ftp://www.google.com", "true");
        testHelper(urlValidator, "file://www.google.com", "true");
        testHelper(urlValidator, "mailto://www.google.com", "true");

        testHelper(urlValidator, "htp://www.google.com", "false");

        testHelper(urlValidator, "http://www.google.com:80", "true");
        testHelper(urlValidator, "http://www.google.com:66666", "false");

        testHelper(urlValidator, "http://www.google.com/news", "true");
        testHelper(urlValidator, "http://www.google.com/..", "false");

        testHelper(urlValidator, "http://www.google.com?action=view", "true");
        testHelper(urlValidator, "http://www.google.comaction=view", "false");

        System.out.println();
    }

    public void testInputPartitions() {
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        System.out.println("Testing VALID partitions, values should be true...");
        schemesPartition(urlValidator, true);
        authorityPartition(urlValidator, true);
        portPartition(urlValidator, true);
        pathPartition(urlValidator, true);
        queryPartition(urlValidator, true);
        System.out.println();
        System.out.println("Testing INVALID partitions, values should be false...");
        schemesPartition(urlValidator, false);
        authorityPartition(urlValidator, false);
        portPartition(urlValidator, false);
        pathPartition(urlValidator, false);
        queryPartition(urlValidator, false);
    }

    private void schemesPartition(UrlValidator urlValidator, boolean isValid) {
        for (String scheme: (isValid ? validSchemes : invalidSchemes)) {
            String url = scheme + "google.com";
            testHelper(urlValidator, url, "" + isValid);
        }
    }

    private void authorityPartition(UrlValidator urlValidator, boolean isValid) {
        for (String authority: (isValid ? validAuthorities : invalidAuthorities)) {
            String url = "http://" + authority;
            testHelper(urlValidator, url, "" + isValid);
        }
    }

    private void portPartition(UrlValidator urlValidator, boolean isValid) {
        for (String port: (isValid ? validPorts : invalidPorts)) {
            String url = "http://google.com" + port;
            testHelper(urlValidator, url, "" + isValid);
        }
    }

    private void pathPartition(UrlValidator urlValidator, boolean isValid) {
        for (String path: (isValid ? validPath : invalidPath)) {
            String url = "http://google.com" + path;
            testHelper(urlValidator, url, "" + isValid);
        }
    }

    private void queryPartition(UrlValidator urlValidator, boolean isValid) {
        for (String query: (isValid ? validQuery : invalidQuery)) {
            String url = "http://google.com" + query;
            testHelper(urlValidator, url, "" + isValid);
        }
    }

    public void testIsValid() {
        Random rand = new Random();
        int numberOfUrlParts = 5;
        int numberOfTests = 100;
        int invalidPart = numberOfUrlParts; // initialized larger than last index

        for (int i = 0; i < numberOfTests; i++) {
            boolean isValid = rand.nextBoolean();
            if (!isValid) {
                // set invalidPart to reachable index if isValid is false
                invalidPart = rand.nextInt(numberOfUrlParts);
            }
            int urlValidatorOption = rand.nextInt(5);
            UrlValidator urlValidator = new UrlValidator(urlValidatorOptions[urlValidatorOption]);

            String url = "";
            for (int j = 0; j < numberOfUrlParts; j++) {
                if (j == invalidPart) {
                    // only concat invalid part if isValid is false
                    // unreachable if invalidPart was never changed
                    url += invalidPartitions[j][rand.nextInt(invalidPartitions[j].length)];
                } else {
                    url += validPartitions[j][rand.nextInt(validPartitions[j].length)];
                }
            }
            testHelper(urlValidator, url, isValid ? "true" : "false");
        }
    }

    // long[] of UrlValidator options
    private static final long[] urlValidatorOptions = {0, UrlValidator.ALLOW_ALL_SCHEMES, UrlValidator.ALLOW_2_SLASHES,
            UrlValidator.NO_FRAGMENTS, UrlValidator.ALLOW_LOCAL_URLS};

    // String[] of URL partitions
    private static final String[] validSchemes = {"", "http://", "https://", "telnet://", "ftp://", "file://", "mailto://"};
    private static final String[] invalidSchemes = {"htp://", "htps://", "click://"};

    private static final String[] validAuthorities = {"www.google.com", "google.com", "google.co.uk", "google.cn", "0.0.0.0", "255.255.255.255", "1.com"};
    private static final String[] invalidAuthorities = {"", "google", "googlecom", "google..com", "256.256.256.256"};

    private static final String[] validPorts = {"", ":0", ":80", ":8080"};
    private static final String[] invalidPorts = {":-1", ":65536", ":a000"};

    private static final String[] validPath = {"", "/valid", "/valid/valid"};
    private static final String[] invalidPath = {"./", ".."};

    private static final String[] validQuery = {"", "?action=view", "?action=edit&mode=up"};
    private static final String[] invalidQuery = {"action=view"};

    private static final String[][] validPartitions = {validSchemes, validAuthorities, validPorts, validPath, validQuery};
    private static final String[][] invalidPartitions = {invalidSchemes, invalidAuthorities, invalidPorts, invalidPath, invalidQuery};
}
