[string]$EXECUTABIL = "Lab2_PPD_matrice.exe" 
[string]$FISIER_REZULTATE = "rezultate_lab2.csv"
[int]$NR_RULARI = 10

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

Write-Host "Generare fisier 'input.bin' o singura data..."
cmd /c ".\$EXECUTABIL gen"
Write-Host ""

Write-Host "Rulare test Secvential ($NR_RULARI ori)..."
$suma_secv = 0.0
for ($i = 1; $i -le $NR_RULARI; $i++) {
    $timp_string = (cmd /c ".\$EXECUTABIL secv")
    try {
        $timp_numeric = [double]::Parse($timp_string, $cultura_invarianta)
        $suma_secv += $timp_numeric
        $linie_csv = "Secvential,1,$i,$($timp_numeric.ToString($cultura_invarianta))"
        Add-Content $FISIER_REZULTATE $linie_csv
        Write-Host " Rulare ${i}: $timp_numeric ms"
    } catch {
        Write-Host " Eroare la rularea ${i} (secv) sau parsarea output-ului: $timp_string" -ForegroundColor Red
    }
}
if ($NR_RULARI -gt 0) {
    $media_secv = $suma_secv / $NR_RULARI
    Add-Content $FISIER_REZULTATE "Secvential (Medie),1,N/A,$($media_secv.ToString($cultura_invarianta))"
    Write-Host "Timp mediu Secvential: $media_secv ms"
}
Write-Host ""

Write-Host "Rulare test Paralel (P=$P_test, $NR_RULARI ori)..."
$suma_paralel = 0.0
for ($i = 1; $i -le $NR_RULARI; $i++) {
    # Ruleaza modul 'paralel P' si captureaza timpul afisat
    $timp_string = (cmd /c ".\$EXECUTABIL paralel $P_test")
    try {
        $timp_numeric = [double]::Parse($timp_string, $cultura_invarianta)
        $suma_paralel += $timp_numeric
        # Actualizeaza eticheta CSV
        $linie_csv = "Paralel,$P_test,$i,$($timp_numeric.ToString($cultura_invarianta))" 
        Add-Content $FISIER_REZULTATE $linie_csv
        Write-Host " Rulare ${i}: $timp_numeric ms"
    } catch {
         Write-Host " Eroare la rularea ${i} (paralel) sau parsarea output-ului: $timp_string" -ForegroundColor Red
    }
}
if ($NR_RULARI -gt 0) {
    $media_paralel = $suma_paralel / $NR_RULARI
    # Actualizeaza eticheta CSV
    Add-Content $FISIER_REZULTATE "Paralel (Medie),$P_test,N/A,$($media_paralel.ToString($cultura_invarianta))" 
    Write-Host "Timp mediu Paralel: $media_paralel ms"
}
Write-Host ""

# Ruleaza verificarea de corectitudine o singura data la final
Write-Host "Rulare verificare corectitudine..."
cmd /c ".\$EXECUTABIL verifica"
Write-Host ""

Write-Host "Gata! Rezultatele au fost salvate in $FISIER_REZULTATE"