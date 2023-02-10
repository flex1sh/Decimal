using System;
using System.IO;

class Example
{  
   static bool print_2val_file(decimal d1,decimal d2,decimal result,string name) {
            int[] bits_d1 = decimal.GetBits(d1);
            int[] bits_d2 = decimal.GetBits(d2);
            int[] bits_result = decimal.GetBits(result);
            string[] str = {$"{name}|"+
                           $"{d1}|{bits_d1[3]}|{bits_d1[2]}|{bits_d1[1]}|{bits_d1[0]}|"+
                           $"{d2}|{bits_d2[3]}|{bits_d2[2]}|{bits_d2[1]}|{bits_d2[0]}|"+
                           $"{result}|{bits_result[3]}|{bits_result[2]}|{bits_result[1]}|{bits_result[0]}"
                           };
            File.AppendAllLines("testing/result_cs.txt", str);
            return true;
   }
   static bool print_2val(decimal d1,decimal d2,decimal result) {
            int[] bits_d1 = decimal.GetBits(d1);
            int[] bits_d2 = decimal.GetBits(d2);
            int[] bits_result = decimal.GetBits(result);
            string[] bits_d1_str = convert(bits_d1);
            string[] bits_d2_str = convert(bits_d2);
            string[] bits_result_str = convert(bits_result);
            for(int i = bits_d1_str.Length-1; i>=0;i--){
               Console.WriteLine($"  bits1[{i}]:    "+bits_d1_str[i]);
               Console.WriteLine($"  bits2[{i}]:    "+bits_d2_str[i]);
               Console.WriteLine($"  bitsRes[{i}]:  "+bits_result_str[i]);
               Console.WriteLine($"");

            }
            return true;
   }

      static decimal sub(string value) {
         string[] subs = value.Split(" ");
         decimal d1;
         decimal d2;
         if( decimal.TryParse(subs[1], out d1) && decimal.TryParse(subs[2], out d2) ) {
            decimal result = d1-d2;
            Console.WriteLine($"decimal.sub ({d1}, {d2}): {result}");
            print_2val(d1,d2,result);
            print_2val_file(d1,d2,result, "sub");
            return result;
         }
         else {
            Console.WriteLine($"overflow ({value})");
            return 0;
         }
      }

   static decimal add(string value) {
         string[] subs = value.Split(" ");
         decimal d1;
         decimal d2;
         if( decimal.TryParse(subs[1], out d1) && decimal.TryParse(subs[2], out d2) ) {
            decimal result = Decimal.Add (d1,d2);
            Console.WriteLine($"decimal.add ({d1}, {d2}): {result}");
            print_2val(d1,d2,result);
            print_2val_file(d1,d2,result, "add");
            return Decimal.Add (d1,d2);
         }
         else {
            Console.WriteLine($"overflow ({value})");
            return 0;
         }
      }

   static string[] convert(int[] bits){
      string[] str={" "," "," "," "};
      for(int j = 0;j<=3;j++){
         str[j] = Convert.ToString(bits[j], 2).PadLeft(32, '0');
      for(int i = 4;i<=35;i+=5){
         str[j] = str[j].Insert(i," ");
      }}
      return str;
   }

   static decimal input_filter(string value){
      decimal result;
      if(value == "MAX")
         return decimal.MaxValue;
      if(value == "MIN")
         return decimal.MinValue;
      if(value == "INT_MAX")
         return 4294967295m;
      if(value == "INT_MIN")
         return -4294967295m;
      if (value.StartsWith("ADD"))
         return add(value);
      if (value.StartsWith("SUB"))
         return sub(value);
      
      if(decimal.TryParse(value, out result))
         return result;
      else{
         Console.WriteLine($"overflow ({value})");
         return 0;
         }
   }

   public static void Main()
   {
      var values = File.ReadAllLines("numbers.txt");
      File.WriteAllText("testing/result_cs.txt","");// очищает файл
      foreach (var value in values) {
         
        decimal value_dec = input_filter(value);
        int[] bits = decimal.GetBits(value_dec);
        string[] bits_str = convert(bits);
        Console.WriteLine($"decimal: {value_dec}");
        for(int i = bits_str.Length-1; i>=0;i--)
        Console.WriteLine($"  bits[{i}]:    "+bits_str[i]);
        Console.WriteLine("");
      }
   }
}