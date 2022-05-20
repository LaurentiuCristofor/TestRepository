/////////////////////////////////////////////
// Copyright (c) Gaia Platform LLC
// All rights reserved.
/////////////////////////////////////////////

import java.io.BufferedReader;
import java.io.FileReader;


import java.util.StringTokenizer;

public class TestJava
{
    protected static final String propertyDelimiter = "|";
    protected static final String keyValueDelimiter = "=";
    protected static final String csvSeparator = ",";

    public static void main(String[] args)
    {
        //TestJava.parsePayload("name=alice|age=32|gender=f|nationality=uk");
        //TestJava.splitString("7S,\\N,RSH,7098,ANI,5967,,0,");
        //TestJava.checkStringWithSpecialCharacters();
        TestJava.testCharPrint();
    }

    protected static void testCharPrint()
    {
        for (byte b = -128; b < 127; b++)
        {
            System.out.print(b);
            System.out.print("    | ");

            if (b >= 32 && b <= 126)
            {
                System.out.print(b);
                System.out.print("    | ");
            }
            else
            {
                System.out.print("    | ");
            }

            char c = (char)b;
            if (!Character.isISOControl(c))
            {
                System.out.print("<");
                System.out.print(c);
                System.out.println(">");
            }
            else
            {
                System.out.println("<unprintable>");
            }
        }
    }

    protected static void parsePayload(String payload)
    {
        if  (payload == null)
        {
            return;
        }

        StringTokenizer payloadTokenizer = new StringTokenizer(payload, propertyDelimiter);
        while (payloadTokenizer.hasMoreTokens())
        {
            String property = payloadTokenizer.nextToken();
            StringTokenizer propertyTokenizer = new StringTokenizer(property, keyValueDelimiter);

            String key = "";
            String value = "";

            if (propertyTokenizer.hasMoreTokens())
            {
                key = propertyTokenizer.nextToken();
            }

            if (propertyTokenizer.hasMoreTokens())
            {
                value = propertyTokenizer.nextToken();
            }

            System.out.println("key = " + key + "; value = " + value);
        }
    }

    protected static void splitString(String line)
    {
        String[] columns = line.split(csvSeparator);

        System.out.println("The line contained " + columns.length + " columns");

        for (int i = 0; i < columns.length; i++)
        {
            System.out.println("Column[i]=[" + columns[i] + "]");
        }
    }

    protected static void checkStringWithSpecialCharacters()
    {
        try
        {
            BufferedReader reader = new BufferedReader(new FileReader("error.dat"));
            String line = reader.readLine();
            System.out.println(line);
            System.out.println(line.getBytes().length);
            line = cleanupString(line);
            System.out.println(line);
            System.out.println(line.getBytes().length);

            line = reader.readLine();
            System.out.println(line);
            System.out.println(line.getBytes().length);
            line = cleanupString(line);
            System.out.println(line);
            System.out.println(line.getBytes().length);
        }
        catch (Exception e)
        {
            System.out.println("An error has occurred: " + e.getMessage());
        }
    }

    protected static String cleanupString(String value)
    {
        if (value.getBytes().length == value.length())
        {
            return value;
        }

        StringBuilder newString = new StringBuilder();
        for (int i = 0; i < value.length(); i++)
        {
            char character = value.charAt(i);

            if (Character.isIdentifierIgnorable(character))
            {
                System.out.println(">>>" + i + " isIdentifierIgnorable");
            }
            if (Character.isHighSurrogate(character))
            {
                System.out.println(">>>" + i + " isHighSurrogate");
            }
            if (Character.isLowSurrogate(character))
            {
                System.out.println(">>>" + i + " isLowSurrogate");
            }
            if (Character.isIdeographic(character))
            {
                System.out.println(">>>" + i + " isIdeographic");
            }
            if (Character.isISOControl(character))
            {
                System.out.println(">>>" + i + " isISOControl");
            }
            if (Character.isSurrogate(character))
            {
                System.out.println(">>>" + i + " isSurrogate");
            }
            if (Character.isTitleCase(character))
            {
                System.out.println(">>>" + i + " isTitleCase");
            }

            // System.out.println(">>>" + i + " block: " + Character.UnicodeBlock.of(character));

            if (Character.isISOControl(character))
            {
                i += 2;
                continue;
            }

            System.out.println(">>>" + i + " " + character);

            newString.append(character);
        }

        value = newString.toString();

        return value;
    }
}
