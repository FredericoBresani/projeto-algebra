import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, CommonModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss'
})
export class AppComponent  implements OnInit {
  
  public title = 'numbers';

  public numbers: number[] = [0];

  public mantissaLength: number = 0;

  public lengthOptions: { text: string; value: number }[] = [];

  public z: number = 0;

  public mantissa: number = 0;

  public validMantissaLength: boolean = false;

  public negativeNumbers: number[] = [];

  public positiveNumbers: number[] = [];

  public precision: number = 0;

  public lastNumber: number = 0;
  
  constructor() {}

  public ngOnInit(): void {
    this.setLengthOptions();
  }

  public setLengthOptions(): void {
    for (let i = 1; i <= 100; i++) {
      this.lengthOptions.push({ text: i.toString(), value: i });
    }
  }

  public openOrCloseOptions(event: Event): void {
    const targetedElement: HTMLElement = event.target as HTMLElement;
    if (targetedElement.getAttribute('class') == 'option') {
      targetedElement.parentElement?.classList.toggle('active-options');
    } else {
      (targetedElement.lastChild as HTMLElement).classList.toggle('active-options');
    }
  }

  public setMantissaLength(n: number): void {
    this.mantissaLength = n;
    if (this.validSetup()) this.generateNumbers();
  }

  public updateZValue(event: Event): void {
    this.z = Number((event.target as HTMLInputElement).value);
    if (this.validSetup()) this.generateNumbers();
  }

  public updateMantissaValue(event: Event): void {
      this.mantissa = Number(Number('0.'+(event.target as HTMLInputElement).value).toFixed(this.mantissaLength));
      if (this.validSetup()) this.generateNumbers();
  }

  public checkMantissaLength(event: Event): void {
    if ((event.target as  HTMLInputElement).value?.length < this.mantissaLength) {
      this.validMantissaLength = true;
    } else {
      this.validMantissaLength = false;
    }
  }

  public updatePrecision(event: Event): void {
    this.precision = Number((event.target as HTMLInputElement).value);
    if (this.validSetup()) this.generateNumbers();
  }

  public validSetup(): boolean {
    return (this.z >= 0 && this.mantissa != 0 && this.mantissaLength != 0 && this.precision > 0);
  }

  public zoomUp(): void {
    if (this.validSetup()) {
      if (this.positiveNumbers.length > 1) {
        const decimalPart = Math.pow(10, this.z);
        const lastNumber = this.positiveNumbers[this.positiveNumbers.length - 2];
        this.lastNumber = lastNumber;
        let interval = lastNumber/this.precision;
        this.positiveNumbers = [];
        this.negativeNumbers = [];
        for (let i = 0; i < this.precision; i++) {
          this.positiveNumbers.push(Number((interval*(i + 1)).toFixed(decimalPart.toString().length - 1)));
          this.negativeNumbers.push(Number((-interval*(i + 1)).toFixed(decimalPart.toString().length - 1)));
          
        }
        this.negativeNumbers = this.negativeNumbers.reverse();
        this.numbers = [];
        this.numbers.push(...this.negativeNumbers);
        this.numbers.push(0);
        this.numbers.push(...this.positiveNumbers);
      }
    }
  }

  public zoomDown(): void {
    if (this.validSetup()) {
      if (this.positiveNumbers.length > 1) {
        let interval = this.positiveNumbers[this.positiveNumbers.length - 1] - this.positiveNumbers[this.positiveNumbers.length - 2];
        const lastNumber = this.positiveNumbers[this.positiveNumbers.length - 1] + interval;
        this.lastNumber = lastNumber;
        
        this.positiveNumbers = [];
        this.negativeNumbers = [];
        for (let i = 0; i < this.precision; i++) {
          this.positiveNumbers.push(interval*(i + 1));
          this.negativeNumbers.push(-interval*(i + 1));
        }
        this.negativeNumbers = this.negativeNumbers.reverse();
        this.numbers = [];
        this.numbers.push(...this.negativeNumbers);
        this.numbers.push(0);
        this.numbers.push(...this.positiveNumbers);
      }
    }
  }

  public generateNumbers(): void {
    const decimalPart = Math.pow(10, this.z);
    const lastNumber = decimalPart * this.mantissa;
    this.lastNumber = lastNumber;
    let interval = lastNumber/this.precision;
    this.positiveNumbers = [];
    this.negativeNumbers = [];
    for (let i = 0; i < this.precision; i++) {
      this.positiveNumbers.push(Number((interval*(i + 1)).toFixed(decimalPart.toString().length)));
      this.negativeNumbers.push(Number((-interval*(i + 1)).toFixed(decimalPart.toString().length)));
      
    }
    this.negativeNumbers = this.negativeNumbers.reverse();
    this.numbers = [];
    this.numbers.push(...this.negativeNumbers);
    this.numbers.push(0);
    this.numbers.push(...this.positiveNumbers);
  }
}
