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
               Console.WriteLine($"  bits1[{i}]:    "+bits_d1_str[i]+$"  : {bits_d1[i]}");
               Console.WriteLine($"  bits2[{i}]:    "+bits_d2_str[i]+$"  : {bits_d2[i]}");
               Console.WriteLine($"  bitsRes[{i}]:  "+bits_result_str[i]+$"  : {bits_result[i]}");
               Console.WriteLine($"");

            }
            return true;
   }

   static decimal sub(string value) {
      string[] subs = value.Split(" - ");
      decimal d1;
      decimal d2;
      if( decimal.TryParse(subs[0], out d1) && decimal.TryParse(subs[1], out d2) ) {
         decimal result = 0m;
         try
         {
            checked {
               result = d1-d2;
               Console.WriteLine($"decimal: ({d1} - {d2}) = {result}");
               print_2val(d1,d2,result);
            }
         }
         catch (OverflowException e) {
            Console.WriteLine($"overflow ({value})");  // output: Arithmetic operation resulted in an overflow.
         }
         print_2val_file(d1,d2,result, "sub");
         return result;
      }
      else {
         Console.WriteLine($"overflow ({value})");
         return 0;
      }
   }

   static decimal div(string value) {
      string[] subs = value.Split(" / ");
      decimal d1;
      decimal d2;
      if( decimal.TryParse(subs[0], out d1) && decimal.TryParse(subs[1], out d2) ) {
         decimal result = Decimal.Divide(d1, d2);
         Console.WriteLine($"decimal: ({d1} / {d2}) = {result}");
         print_2val(d1,d2,result);
         print_2val_file(d1,d2,result, "div");
         return result;
      }
      else {
         Console.WriteLine($"overflow ({value})");
         return 0;
      }
   }

   static decimal mul(string value) {
      string[] subs = value.Split("*");
      decimal d1;
      decimal d2;
      if( decimal.TryParse(subs[0], out d1) && decimal.TryParse(subs[1], out d2) ) {
         decimal result = Decimal.Multiply(d1, d2);
         Console.WriteLine($"decimal: ({d1} * {d2}) = {result}");
         print_2val(d1,d2,result);
         print_2val_file(d1,d2,result, "mul");
         return result;
      }
      else {
         Console.WriteLine($"overflow ({value})");
         return 0;
      }
   }

   static decimal mod(string value) {
      string[] subs = value.Split("%");
      decimal d1;
      decimal d2;
      if( decimal.TryParse(subs[0], out d1) && decimal.TryParse(subs[1], out d2) ) {
         decimal result = d1 % d2;
         Console.WriteLine($"decimal: ({d1} % {d2}) = {result}");
         print_2val(d1,d2,result);
         print_2val_file(d1,d2,result, "mod");
         return result;
      }
      else {
         Console.WriteLine($"overflow ({value})");
         return 0;
      }
   }

   static decimal add(string value) {
         string[] subs = value.Split("+");
         decimal d1;
         decimal d2;
         if( decimal.TryParse(subs[0], out d1) && decimal.TryParse(subs[1], out d2) ) {
            decimal result = Decimal.Add (d1,d2);
            Console.WriteLine($"decimal: ({d1} + {d2}) = {result}");
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
         if(j == 3 && ((i == 19) || (i == 9))){
         if (i == 19) str[j] = str[j].Insert(i,"}");
         if (i == 9) str[j] = str[j].Insert(i,"{");
         }
         else
         str[j] = str[j].Insert(i," ");
      }}
      return str;
   }

   static decimal input_filter(string value){
      decimal result;
      if(value.Contains("INT_MAX"))
         value = value.Replace("INT_MAX","4294967295");
      if(value.Contains("INT_MIN"))
         value = value.Replace("INT_MIN","-4294967295");
      if(value.Contains("MAX"))
         value = value.Replace("MAX",decimal.MaxValue.ToString());
      if(value.Contains("MIN"))
         value = value.Replace("MIN",decimal.MinValue.ToString());
      if (value.Contains("+"))
         return add(value);
      if (value.Contains(" - "))
         return sub(value);
      if (value.Contains("*"))
         return mul(value);
      if (value.Contains(" / "))
         return div(value);
      if (value.Contains("%"))
         return mod(value);
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
         if(!string.IsNullOrEmpty(value) && !value.StartsWith("//")) {
            decimal value_dec = input_filter(value);
            int[] bits = decimal.GetBits(value_dec);
            string[] bits_str = convert(bits);
            Console.WriteLine($"decimal: {value_dec}");
            for(int i = bits_str.Length-1; i>=0;i--)
            Console.WriteLine($"  bits[{i}]:     "+bits_str[i]+$"  : {bits[i]}");
            Console.WriteLine("");
        }
      }
   }
}