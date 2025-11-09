[string]$JAVA_OPTS = "-Xmx4g"
[string]$FISIER_REZULTATE = "rezultate_rulari_java_lab2.csv"
[int]$NR_RULARI = 10

$env:JAVA_OPTS = $JAVA_OPTS

if ($args.Count -eq 0) {
    Write-Host "Eroare: Trebuie sa specifici numarul de thread-uri" -ForegroundColor Red
    return
}
[int]$P_test = $args[0]
if ($P_test -le 0) {
     Write-Host "Eroare: Numarul de thread-uri trebuie sa fie pozitiv." -ForegroundColor Red
     return
}

$cultura_invarianta = [System.Globalization.CultureInfo]::InvariantCulture

if (Test-Path $FISIER_REZULTATE) {
    Remove-Item $FISIER_REZULTATE
}
New-Item $FISIER_REZULTATE -ItemType File
Set-Content $FISIER_REZULTATE 'Varianta,NrThreads,Rulare,TimpExecutie(ms)'

Function Ruleaza-Test($argumente) {
    return (Invoke-Expression ".\gradlew run -q -Pargs=`"$argumente`"")
}

Write-Host "Generare fisier 'input.bin' o singura data..."
Ruleaza-Test "gen"
Write-Host ""

Write-Host "Rulare test Secvential ($NR_RULARI ori)..."
$suma_secv = 0.0
for ($i = 1; $i -le $NR_RULARI; $i++) {
    $timp_string = Ruleaza-Test "secv"
    $timp_numeric = [double]::Parse($timp_string, $cultura_invarianta)
    $suma_secv += $timp_numeric
    $linie_csv = "Secvential,1,$i,$($timp_numeric.ToString($cultura_invarianta))"
    Add-Content $FISIER_REZULTATE $linie_csv
    Write-Host " Rulare ${i}: $timp_numeric ms"
}
$media_secv = $suma_secv / $NR_RULARI
Add-Content $FISIER_REZULTATE "Secvential (Medie),1,N/A,$($media_secv.ToString($cultura_invarianta))"
Write-Host "Timp mediu Secvential: $media_secv ms"
Write-Host ""

Write-Host "Rulare test Paralel (P=$P_test, $NR_RULARI ori)..."
$suma_paralel = 0.0
for ($i = 1; $i -le $NR_RULARI; $i++) {
    $timp_string = Ruleaza-Test "paralel $P_test" # Am schimbat comanda
    $timp_numeric = [double]::Parse($timp_string, $cultura_invarianta)
    $suma_paralel += $timp_numeric
    $linie_csv = "Paralel,$P_test,$i,$($timp_numeric.ToString($cultura_invarianta))" # Am schimbat eticheta
    Add-Content $FISIER_REZULTATE $linie_csv
    Write-Host " Rulare ${i}: $timp_numeric ms"
}
$media_paralel = $suma_paralel / $NR_RULARI
Add-Content $FISIER_REZULTATE "Paralel (Medie),$P_test,N/A,$($media_paralel.ToString($cultura_invarianta))" # Am schimbat eticheta
Write-Host "Timp mediu Paralel: $media_paralel ms" # Am redenumit
Write-Host ""


Write-Host "Se ruleaza verificarea de corectitudine..."
Ruleaza-Test "verifica"
Write-Host ""

Write-Host "Gata! Rezultatele au fost salvate in $FISIER_REZULTATE"