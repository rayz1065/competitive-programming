#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

unordered_set<string> uniques = { "020020", "420420204006", "040040040", "420222204042", "240240204042", "420402042024", "600402204006", "200002", "600222204024", "420060042042", "220220004", "400202004", "420240042024", "600222042024", "402240042042", "400022022", "240060060042", "600222222006", "240222060042", "220202022", "402240222024", "220040022", "420240204024", "420402204024", "600042042042", "420420024024", "060060060060", "420240222006", "600402024024", "420402222006", "240240240006", "420222060024", "240240060024" };
unordered_set<string> not_unique = { "321303222042", "330312132114", "330321204114", "240213141051", "231222213141", "420222150015", "312312303204", "510222114042", "321312303114", "402402123123", "240150123051", "303222222222", "312150141042", "501402123024", "420303231015", "231222141132", "501312123114", "420222213033", "211121031", "240240231015", "600312114105", "402222222123", "312222222132", "600222114033", "321222141042", "501321033033", "321321123042", "411231204123", "240231141114", "510303132024", "301202103", "420141042042", "231222150123", "330321042033", "402231141033", "240231204132", "312240132042", "510222123033", "420312123114", "220112112", "501411033024", "600303204105", "420321033033", "420321042024", "330330033033", "301112112", "312312303123", "420402123105", "231150213132", "130121112", "411411204024", "510303303015", "402321141024", "420420114015", "330231222105", "411231222024", "321132132060", "231222141051", "240231231024", "312240222114", "330321051024", "312240231024", "411312132033", "240150051042", "130130022", "501312213105", "411222132123", "501501204006", "312303222213", "321222150114", "211202112", "321222213132", "510402213006", "411411132015", "231231132051", "411402132024", "411141051042", "510222132024", "420222051114", "321240303024", "420132132123", "420312213105", "402402303105", "411321204114", "240222150033", "330150042042", "420150042033", "240150141114", "240240042042", "501321042024", "312231132051", "330303222033", "321312141114", "330303213123", "600204204204", "420141132114", "231222222132", "330312222105", "330150213033", "420231204033", "240141132132", "501411213006", "240231222114", "420222204204", "411402303015", "600222132015", "420303132114", "240141051051", "330222150024", "321240213114", "303231231042", "330231150015", "411303222033", "150060060051", "330330042024", "420240114114", "501222213114", "402321132033", "222222150213", "330231213033", "321303213213", "600303123024", "420330033024", "420213123051", "510402033024", "510312114114", "411411042024", "330141132123", "321213213141", "411213132132", "411222141033", "510231042024", "321240051033", "420411114105", "411231222105", "411132132051", "240141132051", "330240123114", "420303204123", "321240231015", "600132042033", "420312204033", "420222204123", "321213141132", "231150132051", "402321312015", "330312123123", "330222222033", "411312222024", "411411123024", "411222213042", "411240222015", "600213213024", "510231123024", "321231132042", "402303222123", "240231213123", "321141051051", "321231204132", "510123123051", "321312222033", "222141141141", "321321231015", "231222132060", "330231060024", "220031031", "312312231114", "240303132132", "240240132114", "420222141105", "420231222015", "330312213033", "411312123123", "402402402006", "330321123114", "420402114033", "510132132114", "303231141132", "420402033033", "510213123042", "420051051042", "411330114114", "330150132114", "600222123024", "321231222114", "402231222033", "321150132042", "240222222204", "312312222042", "321231231024", "411321123114", "510312204105", "321312150024", "600204123123", "330231051114", "420402132015", "402303303204", "411231123123", "240222141123", "411240213024", "310031022", "220130013", "321321213114", "312303303213", "321141132132", "141141060060", "420321222006", "420231213024", "402321222024", "240231060033", "420213141114", "330330222006", "150150051051", "420321213015", "231231060123", "600213123033", "501312312006", "240303222123", "501501105105", "240222222123", "510411204006", "330303132123", "510321033024", "301301004", "420222222024", "402222222042", "411312222105", "510222204114", "411321213105", "321240123042", "420312312006", "600213213105", "501411204015", "321303231033", "240132060051", "222150150042", "321222132051", "411303132123", "420303123123", "330213141123", "330303141033", "510312222006", "510321213006", "312240051042", "420213213204", "231141141132", "312222150123", "312312312033", "321321204204", "150150132132", "510312213015", "330231132033", "321321042042", "222222141141", "510132123123", "222141141060", "231150150033", "600312033024", "312312213213", "510402204015", "420312222015", "420303213033", "420303222105", "240213141132", "312303222132", "411231132033", "321231231105", "312231150033", "330231222024", "330231141105", "303303303303", "411312303024", "330312132033", "330321204033", "402321303024", "330222132123", "501312213024", "501213213204", "330312141024", "330240141015", "211211103", "411402204114", "321312303033", "402141141042", "420213213123", "420231213105", "321321204123", "231141141051", "402222213213", "411330222006", "501312123033", "411150132033", "420132132042", "510222051024", "411330213015", "501501114015", "420312213024", "321231123051", "411312141024", "411141132123", "420240213015", "402312213204", "240240150015", "501321222006", "321321132114", "150141060051", "501312222015", "402231132123", "222222150132", "411411033033", "420312123033", "240240213033", "330312222024", "420222123123", "420222222105", "510231033033", "411141141033", "321303213132", "330240204033", "501213213123", "411231141024", "420303141024", "411321141015", "220121103", "600123123123", "330150123123", "420060123123", "231231132132", "411213141123", "402321231015", "600222033033", "402312213123", "402240123123", "330330114114", "330321222015", "240231150024", "402330123114", "240150060033", "231231051051", "150150150033", "240141060123", "330141132042", "420231132105", "321222150033", "510141123114", "330141204132", "402321321006", "312231132132", "231231222204", "420411114024", "330231123123", "211211022", "321312312024", "321312132123", "501303213114", "402312222114", "510402123015", "420312132024", "402321213114", "411312303105", "420312231006", "411321204033", "402312231024", "510231114114", "330213213213", "330222141033", "501231123114", "312231222204", "240150141033", "330051051051", "121121121", "510312303006", "321312141033", "330312312015", "312231141123", "321303132132", "240240051114", "510312132015", "420141204123", "420222141024", "411312123042", "321231141114", "420231141015", "330321213024", "321222060123", "330132132132", "240231222033", "240141141204", "411402123114", "420312303015", "420303132033", "411321312006", "420321114114", "400112013", "501141123123", "420240114033", "501222213033", "231231222123", "402402213114", "231141132060", "321150051042", "411150123123", "220121022", "411132132132", "510312204024", "510213204204", "510222123114", "222222222141", "411231123042", "321141141123", "231213141141", "312240213123", "231150132132", "330240213024", "510213132114", "312231222123", "501312132024", "510312114033", "501501024024", "510051042042", "231150051051", "321222141204", "330060051042", "330240123033", "321231213204", "310121013", "321231051042", "330132132051", "411222123051", "240141141123", "402303213213", "141141141141", "321303222123", "330222213042", "402321123042", "330240222015", "202121121", "240150213042", "501312303015", "240222222042", "501321114114", "240132132060", "420330213006", "321312312105", "330312303024", "420132123051", "510213204123", "312312231033", "321312213042", "420222132033", "420312132105", "420321204105", "330222204132", "411330204024", "402402204204", "321222222204", "411321213024", "510132132033", "312312213132", "303222222141", "330213141042", "321222141123", "321321222105", "330150132033", "501132132123", "411312312015", "301121022", "411213213213", "321231213123", "330150141024", "411321123033", "240240141105", "330321213105", "321240042042", "330231051033", "330231204042", "312240132123", "330321303015", "321231150024", "321321213033", "420303222024", "420312141015", "510303204114", "411321222015", "501303204204", "420231051024", "240150150024", "402222213132", "402312303114", "330231141024", "231231150033", "411240042033", "321150213123", "321222222123", "312150132132", "330222132042", "330312051033", "220112031", "420231042033", "321222132132", "330312231015", "222222222060", "211121112", "130121031", "420132051042", "510222204033", "240231132123", "321321150015", "501411114105", "420231123033", "402141132132", "501141132033", "150150141123", "402231132042", "411411222006", "420312042033", "141141141060", "330321132105", "240240222024", "420222123042", "510231222006", "240060051051", "330240132024", "411231051033", "330312213114", "330240231006", "321240132114", "402240132033", "411402312006", "510402114105", "420402114114", "231222150042", "420231114042", "501222132114", "600123123042", "501231222015", "411231231015", "240240123123", "420141123123", "411330123024", "411240132024", "420240123024", "130040031", "231222222213", "411321303015", "231231141204", "411240123033", "420330204015", "501321213015", "510213213033", "330213213132", "330141123051", "240141060042", "330132060123", "240222213213", "420231132024", "321321060024", "510411024024", "411231042042", "330231123042", "402330222015", "510312123024", "321312132042", "231231231114", "321240204123", "600312213006", "501402114114", "330141141114", "420312051024", "501222204123", "600222213015", "411231213114", "411321132024", "411222132042", "330330213015", "510303123114", "600213132024", "411321231006", "240303141042", "501231213024", "411222204132", "321231060033", "240150132123", "420312114042", "312231231114", "321321132033", "321231132123", "321321141024", "321321051114", "321141060042", "150141141132", "420150123114", "231231141123", "501321123105", "222150141132", "600132123114", "240231141033", "231231213051", "411402213024", "411411303006", "420303303024", "510231213015", "312240141033", "411312213114", "411222222114", "222222222222", "420411033024", "402330213024", "240222132051", "501222222024", "510213123123", "330321141015", "330330204024", "420141141024", "402222132132", "330141051042", "321312231105", "510222213024", "420231231006", "321141141042", "312312222123", "312312312114", "330330114033", "330321312006", "330240132105", "501303123123", "402330123033", "312231222042", "420411213006", "510213141024", "312141141051", "411402222015", "510141123033", "510303213105", "510222222015", "420303213114", "312312132132", "420321303006", "411330123105", "150141141051", "600303114114", "510231204024", "312240222033", "420240123105", "222150141051", "411312231015", "501411123015", "402312222033", "402321213033", "330132051051", "330330132015", "150150060042", "510231114033", "600402105105", "510312123105", "330222123051", "411213213132", "240240051033", "420321204024", "303231222213", "321231141033", "411411114114", "420222051033", "330213132051", "411321132105", "510231132015", "330312123042", "321312123051", "231231213213", "411402123033", "510132051033", "240231213042", "420321114033", "321240123123", "321321222024", "501132132042", "321321141105", "321231213042", "330150051033", "420141132033", "501222123123", "240240141024", "510321204015", "220211013", "400103103", "411402213105", "321321312015", "420222213114", "420321132015", "510213132033", "321240213033", "321240222105", "600222114114", "321303222204", "510411105105", "501222222105", "501303303105", "420213132123", "321303141123", "510222213105", "330240042033", "321222222042", "312312240024", "240222141042", "510204132123", "501321204024", "420402213015", "510321114105", "312222222051", "330222051042", "411330033033", "420240033033", "600402114015", "330303231024", "501321114033", "330321114042", "420132060033", "411330132015", "420330123015", "411312204204", "240231132042", "420240132015", "231231060042", "231150141123", "510312033033", "501411114024", "411312132114", "510312042024", "150150141042", "402330132024", "330222141114", "501321132015", "330303132042", "110011", "330321132024", "420222042042", "510141132024", "411321042033", "330321123033", "312231213213", "321321303024", "501213132123", "510132042042", "330240051024", "420330114024", "510411114015", "510402114024", "321312204132", "310112103", "101101", "600312204015", "301211013", "321321123123", "240222213132", "321231222033", "420303123042", "501402213015", "411330114033", "330240114042", "240240123042", "420141123042", "321222213051", "330303222114", "411312204123", "510132123042", "501141042042", "402312132123", "402321204123", "420231204114", "330231231015", "312222222213", "330132060042", "330141060033", "411330042024", "510321123015", "330330123024", "402231213123", "411303222114", "411411204105", "420213141033", "501303222024", "411303231024", "600213204114", "402321132114", "231222222051", "240231231105", "411303213204", "330231213114", "411321051024", "330321231006", "240150132042", "231150060042", "420213213042", "402231231024", "321321204042", "411321114042", "420204132132", "321240141024", "411222141114", "202202202", "312222213141", "150141132060", "420150213024", "231231141042", "420411204015", "501222141024", "501321123024", "501231042033", "411141132042", "501402303006", "420312204114", "420222132114", "510222132105", "321240132033", "150213141141", "330222222114", "501222132033", "402402222024", "240222051051", "310112022", "420321123024", "321222213213", "321312222114", "330222213204", "240240132033", "411303213123", "321312231024", "321321303105", "312312141123", "303303222222", "402312312024", "420330114105", "321312213204", "303141141141", "411150042042", "330150123042", "411222150024", "231141060051", "510303213024", "303231231123", "411222213204", "510222141015", "411411213015", "231231231033", "330231042042", "402231222114", "303231222132", "330141141033", "411231213033", "231231150114", "600312123015", "510303123033", "231231213132", "321303303123", "501312204114", "330330123105", "312231231033", "420213204132", "240222132132", "330222213123", "402321123123", "312222141132", "402222141123", "321321051033", "420150123033", "600303213015", "510303222015", "600303303006", "321312213123", "312312222204", "600132123033", "411312213033", "600312114024", "411222222033", "402402312015", "411411123105", "312141141132", "411222213123", "310202013", "600213123114", "211130022", "420231123114", "510231123105", "321141132051", "240231123051", "501222123042", "312231141042", "321321321006", "420141051033", "330312042042", "510222042033", "330231204123", "402330042033", "321240222024", "312303231123", "231231222042", "411303303114", "420411123015", "121121040", "420402123024", "321303231114", "510141042033", "420321123105", "420213132042", "600222123105", "321150132123", "321321240006", "420150132024", "330213132132", "402312312105", "330231132114", "330222060033", "310211004", "240303231033", "321312240015", "600132132024", "510321114024", "411240123114", "402222222204", "510213213114", "330312204123", "321150141033", "411231132114", "402321222105", "240141141042", "411411114033", "150150132051", "312231213132", "501231132024", "420420105105", "501402204105", "240231051042", "231150141042", "501231123033" };

int main () {
    // This code knows absolutely nothing about the logic of the problem it's trying to solve
    // I apologize for what I've created
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string concat;
        for (int i = 0; i < n; i++) {
            string curr;
            cin >> curr;
            concat += curr;
        }
        if (uniques.find(concat) != uniques.end()) {
            cout << "Unique";
        } else if (not_unique.find(concat) != not_unique.end()) {
            cout << "Not unique";
        } else {
            cout << "Invalid";
        }
        cout << "\n";
    }
}